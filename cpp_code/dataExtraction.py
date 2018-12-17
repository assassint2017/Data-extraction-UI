# -*- coding:utf-8 -*-
"""

数据提取代码
"""

import argparse
import datetime

import pandas as pd
from numpy import nan

#-------------------------需要设置的部分-------------------------------
# 设定csv文件路径 路径中不要出现中文
# csvDir = 'C:\\Users\\14595\\Desktop\\2018HB example .csv.gz'

# 设定提取csv文件路径 路径中不要出现中文
# extDir = 'C:\\Users\\14595\\Desktop\\ext.csv'

# 各哨点数量汇总文件路径 路径中不要出现中文
# summaryDir = 'C:\\Users\\14595\\Desktop\\summary.csv'

# 设定时间区间
# start = pd.Timestamp(datetime.date(year=2018, month=1, day=1))
# end = pd.Timestamp(datetime.date(year=2018, month=5, day=30))

# 设定选定的地区
# locs = [42010200, 42050300, 42050600]
#---------------------------------------------------------------------

# 命令行代码如下：
# python dataExtraction.py ./test.gz ./ext.csv ./summary.csv 2018 1 1 2018 5 30 42010200 42050300 42050600
# python dataExtraction.py ./test.gz ./ext.csv ./summary.csv 2018 1 1 2018 5 30

# ./dataExtraction.exe ./test.gz ./ext.csv ./summary.csv 2018 1 1 2018 5 30 42010200 42050300 42050600
# ./dataExtraction.exe ./test.gz ./ext.csv ./summary.csv 2018 1 1 2018 5 30

print("正在提取数据，请耐心等待片刻")

parser = argparse.ArgumentParser()

parser.add_argument('csvDir', type=str)
parser.add_argument('extDir', type=str)
parser.add_argument('summaryDir', type=str)

parser.add_argument('startYear', type=int)
parser.add_argument('startMonth', type=int)
parser.add_argument('startDate', type=int)

parser.add_argument('endYear', type=int)
parser.add_argument('endMonth', type=int)
parser.add_argument('endDate', type=int)

parser.add_argument('locs', nargs='*', type=int)
args = parser.parse_args()

# 起始终止日期
start = pd.Timestamp(datetime.date(year=args.startYear, month=args.startMonth, day=args.startDate))
end = pd.Timestamp(datetime.date(year=args.endYear, month=args.endMonth, day=args.endDate))

# 读取csv文件
csv = pd.read_csv(args.csvDir, compression='gzip', encoding='gbk')

# 时间日期格式化处理
csv['诊断时间'] = pd.to_datetime(csv['诊断时间'], format='%Y/%m/%d')

print("初始化完成，开始提取数据")

# 根据条件进行筛选
if len(args.locs) is 0:  
    csv = csv[(csv['诊断时间'] >= start) & (csv['诊断时间'] <= end)]
else: 
    csv = csv[(csv['诊断时间'] >= start) & (csv['诊断时间'] <= end) & (csv['报告单位地区编码'].isin(args.locs))]

# 保存提取数据到csv文件
csv.to_csv(args.extDir, index=0, encoding='gbk')

print("数据提取完毕，开始数据总结")

def removeSpace(item):
    """

    去除在输入过程中误键入的空格
    """
    return item.strip()
csv['录卡用户所属单位'].apply(removeSpace)

temp = pd.value_counts(csv['录卡用户所属单位'])
codes = []
for hospital in list(temp.index):
    index = csv[csv['录卡用户所属单位'] == hospital].index.tolist()[0]
    codes.append(csv['报告单位地区编码'][index])

summary = pd.DataFrame()
summary['报告单位地区编码'] = codes
summary['报告单位'] = list(temp.index)
summary['病例数'] = temp.values

summary.sort_values(by=['报告单位地区编码'], inplace=True)
summary.reset_index(drop=True, inplace=True)

nanlist = []
for i in range(1, len(summary['报告单位地区编码'])):
    if summary.loc[i, '报告单位地区编码'] == summary.loc[i - 1, '报告单位地区编码']:
        nanlist.append(i)

for i in nanlist:
    summary.loc[i, '报告单位地区编码'] = nan

summary.to_csv(args.summaryDir, index=False, encoding='gbk')

print("数据总结完毕，提取完毕")