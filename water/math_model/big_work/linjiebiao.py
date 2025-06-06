def parse_to_adjlist(text):
    adj = {}
    for line in text.strip().splitlines():
        parts = line.strip().split('|')
        parts = [p for p in parts if p.strip()]
        if len(parts) != 3:
            continue
        u, v, w = map(int, [p.strip() for p in parts])
        # 无向图：两端都加
        adj.setdefault(u, []).append((v, w))
        adj.setdefault(v, []).append((u, w))
    return adj

# 示例输入（可粘贴多行）
input_text = """
| 31   | 29   | 1598 |
| 31   | 28   | 1786 |
| 28   | 30   | 474  |
| 28   | 29   | 188  |
| 28   | 27   | 568  |
| 28   | 23   | 841  |
| 30   | 27   | 617  |
| 30   | 7    | 685  |
| 27   | 7    | 1117 |
| 27   | 6    | 571  |
| 27   | 17   | 523  |
| 27   | 18   | 1050 |
| 27   | 4    | 733  |
| 27   | 23   | 658  |
| 23   | 4    | 304  |
| 23   | 24   | 642  |
| 23   | 25   | 1112 |
| 23   | 26   | 3028 |
| 7    | 1    | 459  |
| 7    | 6    | 546  |
| 6    | 5    | 232  |
| 6    | 17   | 450  |
| 17   | 5    | 412  |
| 17   | 16   | 405  |
| 17   | 11   | 690  |
| 17   | 3    | 1016 |
| 17   | 13   | 587  |
| 17   | 18   | 536  |
| 17   | 4    | 1028 |
| 18   | 13   | 355  |
| 18   | 12   | 755  |
| 18   | 15   | 333  |
| 18   | 19   | 362  |
| 18   | 4    | 876  |
| 4    | 28   | 862  |
| 4    | 19   | 1040 |
| 4    | 24   | 347  |
| 4    | 25   | 810  |
| 24   | 19   | 706  |
| 24   | 20   | 857  |
| 24   | 21   | 523  |
| 24   | 25   | 463  |
| 25   | 21   | 720  |
| 1    | 8    | 696  |
| 1    | 2    | 117  |
| 1    | 16   | 406  |
| 1    | 5    | 281  |
| 5    | 2    | 292  |
| 5    | 16   | 280  |
| 16   | 2    | 284  |
| 16   | 3    | 912  |
| 16   | 11   | 617  |
| 16   | 13   | 594  |
| 11   | 3    | 295  |
| 11   | 12   | 256  |
| 11   | 13   | 157  |
| 11   | 15   | 599  |
| 3    | 2    | 1213 |
| 3    | 1    | 1318 |
| 3    | 14   | 818  |
| 3    | 12   | 159  |
| 13   | 12   | 398  |
| 13   | 15   | 453  |
| 12   | 14   | 631  |
| 12   | 15   | 582  |
| 15   | 14   | 565  |
| 15   | 20   | 882  |
| 15   | 19   | 342  |
| 19   | 14   | 941  |
| 19   | 20   | 707  |
| 19   | 21   | 887  |
| 20   | 14   | 820  |
| 20   | 32   | 141  |
| 20   | 33   | 93   |
| 20   | 21   | 563  |
| 20   | 22   | 716  |
| 8    | 9    | 298  |
| 9    | 10   | 240  |
"""

adj_list = parse_to_adjlist(input_text)

# 输出邻接表
for node in sorted(adj_list):
    print(f"{node}: {adj_list[node]},")
