## 对象

- 标签 局部性原理
- 大小 分块
- 三份备份

## 硬盘

- 存储单元，大小为 1
- 磁头单向移动，环形移动

## 事件

- 时间片对齐
- 删除、写入，瞬间
  - (id, size, tag) 对于每个副本，给出硬盘编号，写入位置。
- 读取
  - (req_id, id) 请求的识别码和对象的识别码
  - 磁头 每个时间片固定消耗 G
    - Jump  随机跳 G
    - Pass next 1
    - 首次Read 64 随后 $max(16, ceil(pre\_token * 0.8))$

## 初始化

时间片+105，标签数，硬盘数，存储单元数，令牌数

`fre_del[i][j]` 标签为 i 的对象在 $(j − 1) ∗ 1800 + 1 \le id \le j ∗ 1800$ 时间片的大小和

`fre_write[i][j]`

`fre_read[i][j]`

## 时间片

- TIMESTAMP id
- n_delete 数量
  - id
  - id ... 
- 返回 
  - n_abort 取消请求数量
  - id
  - id ...

- n_write 数量
  - id size tag
  - ...
- 返回
  - obj_id[1]
  - （硬盘号 存储单元号） * 3
  - ...
- n_read 数量
  - req_id，obj_id 
  - ...
- 返回
  - N行运动方式 j n / prprprp#
  - n_rsp 请求完成个数
  - id ...