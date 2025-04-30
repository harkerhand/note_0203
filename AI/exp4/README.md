# 实验报告

## 实验名称

本地部署大模型：提示词工程对大模型输出的影响

## 实验目的  
1. 理解提示词工程的概念及其在大模型中的应用。
2. 掌握本地部署大型模型的实践操作步骤。
3. 分析不同提示词工程如何影响模型生成的结果。

## 实验背景  
随着大语言模型的广泛应用，提示词工程（Prompt Engineering）作为一种调优手段，已成为提升模型生成质量的关键技术之一。通过精心设计提示词，可以引导模型生成更符合需求的输出。在本实验中，我们将探讨不同提示词策略对大语言模型（如Llama模型）生成输出的影响，并通过机器翻译任务评估这些策略的有效性。

## 实验流程  

### 1. 环境部署  
选择基于自监督学习（SAM）的`Llama`模型，并使用`llama_cpp`库进行本地部署。模型使用`Qwen2.5-3B-Instruct`模型文件进行推理。

### 2. 进行实验
设计并测试不同类型的提示词：
   - 标准：“Translate the following sentence to Chinese: ”
   - 增强上下文：“Translate the following sentence into formal Chinese, keeping the context in mind: ”
   - 风格化翻译：“Translate the following English sentence into casual Chinese: ”
   - 带有情感：“Translate the following sentence into Chinese with a sad tone: ”
   - 翻译为日语：“Translate the following sentence to Japanese: ”

   对每个句子使用不同提示词进行翻译，并记录模型输出。

### 3. 结果分析  

- 标准：翻译结果正常，但存在一些冗余输入
    ```text
    reference: 他企图说谎。
    candidate: 他 tends to 说谎 。 
    根据中文习惯,这个句子可以翻译为:  他 tends to 说谎 。 
    或者更自然地,  他 偏爱 说谎 。 
    所以, 最常见的翻译是:  他 偏爱 说谎 。
    ```
- 增强上下文：翻译结果会加入一些上下文内容
    ```text
    reference: 他努力學習。
    candidate: He studied hard. 
    (在学习方面) 他很用功。
    ```
- 风格化翻译：翻译结果存在一些风格化分析
    ```text
    reference: 你們有小孩嗎?
    candidate: Do you have kids?  简单翻译成中文就是 "你有小孩吗？"  用更口语一些的表达方式,  也可以说是 "你小孩多不?"
    小孩多不就是 "你有小孩儿多不" 的意思,  也是更常见的问法.  因此,  最近一些流行的翻译是 "你小孩儿多不？"  也挺顺口的.
    ```
- 带有情感：翻译结果存在较大混乱，可能为模型过小，也有可能是幻觉
    ```text
    reference: 照顾好自己。
    candidate: The translated sentence with a sad tone in Chinese is:  你好，很怀念你。 (Nǐ hǎo hěn huímiǎn nǐ)
    Or more naturally, it can be:  你好，很牵挂你。 (Nǐ hǎo hěn guāqiá nǐ)
    ```
- 翻译为日语：翻译结果为日语，符合要求
    ```text
    reference: 在这等着。
    candidate: The translated sentence for "Wait here." in Japanese is "ここに待ってください." (Koko ni tai sure kudasai. )
    ```

根据实验结果，不同的提示词策略对翻译质量有显著影响。通过加入上下文信息和指定翻译风格，模型能够生成更符合目标要求的翻译内容。特别是在涉及正式或特定语境时，增强提示词的具体性能有效提高翻译的相关性和准确性。

## 结论  
1. **提示词工程影响输出质量**：实验表明，精确设计的提示词能够有效提升翻译结果的质量，特别是在长句子和特定语境下。
2. **上下文敏感的提示词更有效**：加入语境或背景信息的提示词相比简单的翻译指令，能显著提高翻译的准确性和自然度。
3. **提示词长度和结构的调整**：更长或结构化的提示词可以帮助模型理解上下文，提高生成质量。
