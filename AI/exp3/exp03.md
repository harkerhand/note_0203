# 人工智能概论第三次实验报告

**学号**：09023321
**姓名**：巩皓锴

## 实验内容

补全transformer的注意力机制，完成机器翻译任务。

## 实验代码

[代码相对路径链接](./model/attention.py)

```python
class MultiHeadedAttention(nn.Module):
    def __init__(self, h, d_model, dropout=0.1):
        super(MultiHeadedAttention, self).__init__()
        # 保证可以整除
        assert d_model % h == 0

        # 请在以下区域补全__init__函数的代码
        # h为注意力头的数量
        # d_model为模型隐藏层的维度
        # dropout为丢弃率
        self.h = h  # 头数量
        self.d_k = d_model // h  # 每个头的维度
        self.d_model = d_model  # 模型维度
        
        # 创建4个线性投影层，用于转换query, key, value和输出
        # 使用clones函数来创建4个相同参数的线性层，但它们的权重会在训练中分别更新
        self.linears = clones(nn.Linear(d_model, d_model), 4)
        
        # 注意力权重的dropout
        self.dropout = nn.Dropout(p=dropout)

    def forward(self, query, key, value, mask=None):
        # 请在以下区域完成forward函数的代码
        # 注意：此时query, key, value相等，均为该层的输入，需要通过线性层得到新的query, key, value
        # mask为掩码，该函数需要在不同掩码的情况下均适用

        if mask is not None:
            mask = mask.unsqueeze(1)
        
        nbatches = query.size(0)
        
        # 1) 对query, key, value进行线性变换
        query, key, value = [
            lin(x).view(nbatches, -1, self.h, self.d_k).transpose(1, 2)
            # 绑定线性层和输入
            for lin, x in zip(self.linears, (query, key, value))
        ]
        
        # 2) 计算注意力分数
        x = self.attention(query, key, value, mask=mask, dropout=self.dropout)
        
        # 3) 拼接多头的结果并进行最后的线性变换
        x = x.transpose(1, 2).contiguous().view(nbatches, -1, self.d_model)
        
        return self.linears[-1](x)
    
    def attention(self, query, key, value, mask=None, dropout=None):
        d_k = query.size(-1)
        # 计算注意力分数
        scores = torch.matmul(query, key.transpose(-2, -1)) / math.sqrt(d_k)
        
        if mask is not None:
            # 设为最小值来盖住无效的注意力分数
            scores = scores.masked_fill(mask == 0, -1e9)
        
        # 对注意力分数进行softmax得到概率
        p_attn = F.softmax(scores, dim=-1)
        
        # 应用dropout
        if dropout is not None:
            p_attn = dropout(p_attn)
        
        # 用注意力权重对value进行加权求和
        return torch.matmul(p_attn, value)
```

## 实验结果

**模型训练评估如下**：

```text
>>>>> Evaluate
<<<<< Evaluate loss: 4.255829
>>>>> Evaluate
<<<<< Evaluate loss: 2.794638
>>>>> Evaluate
<<<<< Evaluate loss: 1.791476
>>>>> Evaluate
<<<<< Evaluate loss: 1.211943
>>>>> Evaluate
<<<<< Evaluate loss: 0.931070
```

在训练过程中，模型的损失逐渐减小，说明模型在学习。符合预期 \^_\^

**推理验证输入：**

```text
src_vocab 6309
tgt_vocab 3439
>>>>>>> start evaluate

BOS take care . EOS
BOS 照 顾 好 自 己 。 EOS
translation: 照 顧 水 。

BOS wait here . EOS
BOS 在 这 等 着 。 EOS
translation: 在 這 裡 等 。

BOS well done ! EOS
BOS 做 得 好 ！ EOS
translation: 好 ！

BOS he UNK me . EOS
BOS 他 向 我 施 压 。 EOS
translation: 他 給 我 。

BOS he studied hard . EOS
BOS 他 努 力 學 習 。 EOS
translation: 他 努 力 學 。

BOS he UNK easily . EOS
BOS 他 很 容 易 觉 得 累 。 EOS
translation: 他 很 容 易 。

BOS he tends to lie . EOS
BOS 他 企 图 说 谎 。 EOS
translation: 他 很 容 易 。

BOS he was very old . EOS
BOS 他 很 老 。 EOS
translation: 他 非 常 老 。

BOS do you have kids ? EOS
BOS 你 們 有 小 孩 嗎 ? EOS
translation: 你 有 小 孩 吗 ？

BOS do you like snow ? EOS
BOS 你 喜 欢 雪 吗 ？ EOS
translation: 你 喜 歡 雪 嗎 ？

BOS do you live here ? EOS
BOS 你 住 這 裡 嗎 ? EOS
translation: 你 住 在 這 裡 嗎 ？

BOS do you need help ? EOS
BOS 你 需 要 幫 助 嗎 ？ EOS
translation: 你 需 要 帮 助 吗 ？

BOS do you trust her ? EOS
BOS 你 相 信 她 嗎 ? EOS
translation: 你 相 信 她 嗎 ？

BOS she 's my classmate . EOS
BOS 她 是 我 的 同 學 。 EOS
translation: 她 是 我 的 同 。

BOS tom died in battle . EOS
BOS 湯 姆 在 戰 鬥 中 死 了 。 EOS
translation: 汤 姆 在 战 斗 。

BOS when will you leave ? EOS
BOS 你 什 么 时 候 离 开 ？ EOS
translation: 你 什 么 时 候 离 开 ？

BOS she 's very beautiful . EOS
BOS 她 非 常 漂 亮 。 EOS
translation: 她 非 常 漂 亮 。

BOS should we be worried ? EOS
BOS 我 們 應 該 要 擔 心 嗎 ？ EOS
translation: 我 们 应 该 擔 心 吗 ？

BOS some bugs were fixed . EOS
BOS 一 些 程 式 錯 誤 被 改 正 了 。 EOS
translation: 一 些 巧 克 力 。

BOS your answer is wrong . EOS
BOS 你 的 回 答 是 错 的 。 EOS
translation: 你 的 答 你 的 。

BOS that looks like blood . EOS
BOS 那 看 起 来 像 血 。 EOS
translation: 看 起 来 看 。

BOS do you have a tv ? EOS
BOS 你 有 电 视 吗 ？ EOS
translation: 你 有 电 视 机 吗 ？

BOS do you own a gun ? EOS
BOS 你 拥 有 枪 支 吗 ？ EOS
translation: 你 是 个 护 士 嗎 ？

BOS that 's a good idea . EOS
BOS 那 是 一 個 好 主 意 。 EOS
translation: 那 是 個 好 主 。

BOS that 's a good plan . EOS
BOS 那 是 一 個 很 好 的 計 劃 。 EOS
translation: 那 是 一 個 好 主 。

BOS i built a new house . EOS
BOS 我 盖 了 栋 新 房 子 。 EOS
translation: 我 给 我 一 个 新 的 。

BOS i can come at three . EOS
BOS 我 三 點 鐘 可 以 來 。 EOS
translation: 我 三 年 前 。

BOS your dog is very big . EOS
BOS 您 的 狗 非 常 胖 。 EOS
translation: 你 的 狗 非 常 大 。

BOS your dog is very big . EOS
BOS 你 的 狗 非 常 胖 。 EOS
translation: 你 的 狗 非 常 非 常 。

BOS that is useless to me . EOS
BOS 那 對 我 沒 有 用 處 。 EOS
translation: 那 不 用 我 。
Corpus BLEU: 0.27249228441785184
<<<<<<< finished evaluate
```

### 结果分析

- 简单句子翻译较好，如"你喜欢雪吗？"、"她非常漂亮"
- 对于部分句子，翻译不完整，如"她是我的同學"只翻译出"她是我的同"
- 某些复杂句子理解有偏差，如"你拥有枪支吗？"被翻译为"你是个护士嗎？"
- BLEU分数为0.272，表明翻译质量中等

整体上，模型在简单句子上表现较好，但在复杂句子上仍有提升空间，可能是由于训练数据量较小，模型未能充分学习复杂句子的翻译规律。

## 实验分析

### 实验过程

1. 使用 uv 管理 python 虚拟环境，安装依赖 torch，nltk，numpy。

    其中，nltk 需要下载 punkt_tab，使用指令：

    ```bash
    python -c "import nltk; nltk.download('punkt_tab')"
    ```

2. 补全 [attention.py](./model/attention.py) 中的 MultiHeadedAttention 类，完成注意力机制的实现。

3. 以训练模式运行 [run.py](./run.py)，训练模型。

4. 以评估模式运行 [run.py](./run.py)，评估模型（程序参数 --type evaluate）。

### 实验总结

本次实验主要实现了 transformer 模型中的多头注意力机制，并在机器翻译任务中进行了验证。通过训练和评估模型，观察到模型在简单句子上的翻译效果较好，但在复杂句子上仍有提升空间。