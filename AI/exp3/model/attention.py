import torch
import math, copy
import torch.nn.functional as F
import torch.nn as nn

from utils import clones



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

