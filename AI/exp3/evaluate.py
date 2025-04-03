import torch
import numpy as np
import time

from parser1 import args
from torch.autograd import Variable
from utils import subsequent_mask
from nltk.translate.bleu_score import corpus_bleu, SmoothingFunction
from collections import defaultdict

def log(data, timestamp):
    file_path = f'log/log-{timestamp}.txt'
    file = open(file_path, 'a', encoding='utf-8')
    file.write(data)
    file.write('\n')
    file.close()

    return file_path

def greedy_decode(model, src, src_mask, max_len, start_symbol):
    memory = model.encode(src, src_mask)
    ys = torch.ones(1, 1).fill_(start_symbol).type_as(src.data)
    for i in range(max_len-1):
        out = model.decode(memory, src_mask, 
                           Variable(ys), 
                           Variable(subsequent_mask(ys.size(1))
                                    .type_as(src.data)))
        prob = model.generator(out[:, -1])
        _, next_word = torch.max(prob, dim = 1)
        next_word = next_word.data[0]
        ys = torch.cat([ys, 
                        torch.ones(1, 1).type_as(src.data).fill_(next_word)], dim=1)
    return ys

def parse_data(data):
    test_cases = []
    current_case = defaultdict(list)
    
    for line in data.strip().split('\n'):
        line = line.strip()
        if not line:
            continue
            
        if line.startswith("BOS"):
            if "source" not in current_case:
                current_case["source"] = line.split()[1:-1]  # 去除BOS/EOS
            else:
                current_case["reference"].append(line.split()[1:-1])
                
        elif line.startswith("translation:"):
            current_case["candidate"] = line.split()[1:-1]  # 去除结尾标点
            test_cases.append({
                "source": current_case["source"],
                "references": current_case["reference"],
                "candidate": current_case["candidate"]
            })
            current_case = defaultdict(list)
            
    return test_cases

def parse_translation_file(file_path):
    test_cases = []
    current_case = defaultdict(list)
    
    with open(file_path, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
                
            if line.startswith("BOS"):
                # 处理源句或参考翻译
                tokens = line.split()[1:-1]  # 去除BOS/EOS
                if not current_case.get("source"):
                    current_case["source"] = tokens
                else:
                    current_case["references"].append(tokens)
                    
            elif line.startswith("translation:"):
                # 处理模型输出并完成当前用例
                candidate = line.split()[1:-1]  # 去除最后的标点
                current_case["candidate"] = candidate
                test_cases.append({
                    "source": current_case["source"],
                    "references": current_case["references"],  # 支持多个参考翻译
                    "candidate": current_case["candidate"]
                })
                current_case = defaultdict(list)
                
    return test_cases
def calculate_bleu(test_cases):
    references = [case["references"] for case in test_cases]  # 三维结构：[[[ref1], [ref2], ...], ...]
    candidates = [case["candidate"] for case in test_cases]   # 二维结构：[[token1, token2], ...]

    # 验证数据格式
    def check_tokens(obj):
        """确保所有分词都是字符串"""
        if isinstance(obj, list):
            return [check_tokens(item) for item in obj]
        if not isinstance(obj, str):
            raise TypeError(f"非字符串分词存在: {type(obj)} - {obj}")
        return obj

    references = check_tokens(references)
    candidates = check_tokens(candidates)

    # 使用平滑方法
    smoothie = SmoothingFunction().method1
    
    # 计算整体BLEU
    corpus_score = corpus_bleu(
        references,
        candidates,
        smoothing_function=smoothie
    )
    
    # 计算逐句BLEU
    for case in test_cases:
        case["bleu"] = corpus_bleu(
            [case["references"]],  # 保持三维结构
            [case["candidate"]],   # 保持二维结构
            smoothing_function=smoothie
        )
    
    return corpus_score, test_cases

def evaluate(data, model):
    timestamp = time.time()
    with torch.no_grad():
        for i in range(len(data.dev_en)):
            en_sent = " ".join([data.en_index_dict[w] for w in data.dev_en[i]])
            print("\n" + en_sent)
            log(en_sent, timestamp)
            cn_sent = " ".join([data.cn_index_dict[w] for w in data.dev_cn[i]])
            print("".join(cn_sent))
            log(cn_sent, timestamp)

            src = torch.from_numpy(np.array(data.dev_en[i])).long().to(args.device)
            src = src.unsqueeze(0)
            src_mask = (src != 0).unsqueeze(-2)

            out = greedy_decode(model, src, src_mask, max_len = args.max_length, start_symbol = data.cn_word_dict["BOS"])

            translation = []
            for j in range(1, out.size(1)):
                sym = data.cn_index_dict[out[0, j].item()]
                if sym != 'EOS':
                    translation.append(sym)
                else:
                    break
            print("translation: %s" % " ".join(translation))
            file_path=log("translation: " + " ".join(translation) + "\n", timestamp)
            
    test_cases=parse_translation_file(file_path)
    corpus_score, test_cases = calculate_bleu(test_cases)
    print(f"Corpus BLEU: {corpus_score}")
    
    
        
       
            

