import random
import copy
      


def a_star(start_state, goal_state):
    
    moves = []
    # 请在以下区域完成启发式函数的代码
    
    import heapq
    # 定义曼哈顿距离启发函数
    def manhattan_distance(state, goal):
        distance = 0
        # 创建数字位置映射表
        goal_positions = {}
        for i in range(5):
            for j in range(5):
                goal_positions[goal[i][j]] = (i, j)
        
        # 计算每个数字的曼哈顿距离之和
        for i in range(5):
            for j in range(5):
                if state[i][j] != 0:  # 跳过空白格
                    goal_i, goal_j = goal_positions[state[i][j]]
                    distance += abs(i - goal_i) + abs(j - goal_j)
        return distance
    
    # 定义方向移动
    directions = {
        'UP': (-1, 0),
        'DOWN': (1, 0),
        'LEFT': (0, -1),
        'RIGHT': (0, 1)
    }
    
    # 查找空白格位置
    def find_blank(state):
        for i in range(5):
            for j in range(5):
                if state[i][j] == 0:
                    return i, j
        return -1, -1
    
    # 生成下一个状态
    def get_next_states(state, blank_x, blank_y):
        next_states = []
        for dir_name, (dx, dy) in directions.items():
            new_x, new_y = blank_x + dx, blank_y + dy
            if 0 <= new_x < 5 and 0 <= new_y < 5:
                new_state = copy.deepcopy(state)
                new_state[blank_x][blank_y], new_state[new_x][new_y] = new_state[new_x][new_y], new_state[blank_x][blank_y]
                next_states.append((new_state, dir_name, (new_x, new_y)))
        return next_states
    
    # 将状态转为元组，便于哈希
    def state_to_tuple(state):
        return tuple(tuple(row) for row in state)
    
    # 开始A*搜索
    start_blank_x, start_blank_y = find_blank(start_state)
    initial_h = manhattan_distance(start_state, goal_state)
    
    # 优先队列(f值, g值, 状态, 空白格坐标, 路径)
    open_list = [(initial_h, 0, start_state, (start_blank_x, start_blank_y), [])]
    closed_set = set()  # 已访问状态集合
    
    while open_list:
        # 取出f值最小的状态
        f, g, current_state, (blank_x, blank_y), path = heapq.heappop(open_list)
        
        # 状态转元组用于哈希检查
        state_tuple = state_to_tuple(current_state)
        
        # 如果是目标状态，返回路径
        if state_tuple == state_to_tuple(goal_state):
            return path
        
        # 如果已经访问过此状态，则跳过
        if state_tuple in closed_set:
            continue
        
        # 标记为已访问
        closed_set.add(state_tuple)
        
        # 生成所有可能的下一步状态
        for next_state, direction, (new_blank_x, new_blank_y) in get_next_states(current_state, blank_x, blank_y):
            next_state_tuple = state_to_tuple(next_state)
            
            # 如果该状态已访问过，则跳过
            if next_state_tuple in closed_set:
                continue
            
            # 计算新的g值和h值
            new_g = g + 1
            new_h = manhattan_distance(next_state, goal_state)
            new_f = new_g + new_h
            
            # 添加到开放列表
            heapq.heappush(open_list, (new_f, new_g, next_state, (new_blank_x, new_blank_y), path + [direction]))
    
    # 如果无解，返回空列表
    return moves


def opposite_direction(direction):
    """返回相反方向"""
    return {
        'UP': 'DOWN',
        'DOWN': 'UP',
        'LEFT': 'RIGHT',
        'RIGHT': 'LEFT'
    }.get(direction, '')


def generate_24_puzzle(goal, steps=50):
    """
    生成可解的24数码初始状态
    :param goal: 目标状态（5x5矩阵）
    :param steps: 随机移动步数
    :return: (初始状态, 解路径)
    """
    current = copy.deepcopy(goal)
    path = []
    directions = {
        'UP': (-1, 0),
        'DOWN': (1, 0),
        'LEFT': (0, -1),
        'RIGHT': (0, 1)
    }
    
    x, y = 4, 4  # 初始空白位置（目标状态0的位置）
    
    for _ in range(steps):
        valid_moves = []
        # 生成所有可能移动方向
        for dir_name, (dx, dy) in directions.items():
            new_x, new_y = x + dx, y + dy
            if 0 <= new_x < 5 and 0 <= new_y < 5:
                # 避免立即回退
                if path and dir_name == opposite_direction(path[-1]):
                    continue
                valid_moves.append((dir_name, dx, dy))
        
        if valid_moves:
            # 随机选择有效移动
            move_info = random.choice(valid_moves)
            dir_name, dx, dy = move_info
            new_x, new_y = x + dx, y + dy
            
            # 执行移动
            current[x][y], current[new_x][new_y] = current[new_x][new_y], current[x][y]
            x, y = new_x, new_y
            path.append(dir_name)
    
    return current, path[::-1]


# 24数码专用验证函数
def is_solvable_24(start, goal):
    """
    验证24数码问题的可解性
    :param start: 初始状态（5x5）
    :param goal: 目标状态（5x5）
    :return: bool
    """
    def count_inversions(matrix):
        """计算逆序数（忽略空白块）"""
        flat = [num for row in matrix for num in row if num != 0]
        inversions = 0
        for i in range(len(flat)):
            for j in range(i+1, len(flat)):
                if flat[i] > flat[j]:
                    inversions += 1
        return inversions
    
    # 5x5拼图（奇数阶）只需比较逆序数奇偶性
    start_inv = count_inversions(start)
    goal_inv = count_inversions(goal)
    
    return (start_inv % 2) == (goal_inv % 2)

# 目标状态定义
GOAL_24 = [
    [1, 2, 3, 4, 5],
    [6, 7, 8, 9, 10],
    [11, 12, 13, 14, 15],
    [16, 17, 18, 19, 20],
    [21, 22, 23, 24, 0]
]

if __name__ == "__main__":
    # 生成测试用例
    start_state, solution_path = generate_24_puzzle(GOAL_24, steps=30)
    
    # 打印生成的初始状态
    print("生成的初始状态：")
    for row in start_state:
        print([f"{num:2d}" for num in row])
    
    # 验证可解性
    print("\n可解性验证:", "通过" if is_solvable_24(start_state, GOAL_24) else "失败")
    
    # 打印理论解信息
    print(f"\n参考解步数: {len(solution_path)}")
    print("参考解:", solution_path)
    
    # 实际解验证（需要已修正的A*算法）
    try:
         # 假设之前的A*算法已保存为previous_code.py
        print("\n运行A*算法验证...")
        actual_solution = a_star(start_state, GOAL_24)
        
        if actual_solution:
            print(f"实际找到解（{len(actual_solution)}步）")
            print("解:", actual_solution)
       
        else:
            print("错误：未找到解")
    except ImportError:
        print("\n（需要已修正的A*算法实现来进行完整验证）")