%% 叠加实现===============================

% 技能伤害
skill_damage = [5,4,3,2,1];

% 技能释放时间线
time_line = 10;
damage_time_line = zeros(1, time_line);

% 技能释放时间
skill_times = [1,2,3];

% 累加每次技能的掉血
for i = 1:length(skill_times)
    start_idx = skill_times(i);
    end_idx = start_idx + length(skill_damage) - 1;
    damage_time_line(start_idx:end_idx) = damage_time_line(start_idx:end_idx) + skill_damage;
end


% 画出累计掉血曲线
stem(1:time_line, damage_time_line, 'filled');
title('小怪累计掉血量（叠加实现）');
xlabel('时间 (秒)');
ylabel('每秒掉血量');
grid on;

%% 卷积实现===============================
clear; clc; close all;

% 技能释放序列 (3次技能，每秒一次)
skill_sequence = [1, 1, 1];

% 单次技能掉血效果
skill_damage = [5, 4, 3, 2, 1];

% 卷积实现累计掉血
total_damage = conv(skill_sequence, skill_damage);

% 画图
stem(1:length(total_damage), total_damage, 'filled');
title('小怪累计掉血量 (卷积实现)');
xlabel('时间 (秒)');
ylabel('每秒掉血量');
grid on;
