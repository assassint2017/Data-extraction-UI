"""

UI脚本
"""
import os
import datetime
from time import time

import tkinter as tk
from tkinter import ttk
import tkinter.messagebox 
from tkinter.filedialog import askopenfilename
from tkinter.filedialog import askdirectory

import pandas as pd

from dataExtraction import dataExtraction


def getData():
    """
    
    获取数据，传递给数据提取函数
    """
    if tk.messagebox.askyesno(title='确认', message='确认开始提取数据？'):

        startTime = time()

        startyear = int(startYear.get())
        startmonth = int(startMonth.get())
        startdate = int(startDate.get())

        endyear = int(endYear.get())
        endmonth = int(endMonth.get())
        enddate = int(endDate.get())

        # 如果只选终止日期的话，意思是选择历史到终止日期的全部数据
        if whetherChooseStartDate.get() == 0 and whetherChooseEndDate.get() == 1:
            start = pd.Timestamp(datetime.date(year=1900, month=1, day=1))
            end = pd.Timestamp(datetime.date(year=endyear, month=endmonth, day=enddate))

        # 如果只选择起始日期的话，意思是选择从起始日期到今天的数据
        if whetherChooseStartDate.get() == 1 and whetherChooseEndDate.get() == 0:
            
            # 获取今天的日期
            temp = datetime.datetime.now().strftime('%Y-%m-%d').split('-')
            nowyear = int(temp[0])
            nowmonth = int(temp[1])
            nowdate = int(temp[2])

            start = pd.Timestamp(datetime.date(year=startyear, month=startmonth, day=startdate))
            end = pd.Timestamp(datetime.date(year=nowyear, month=nowmonth, day=nowdate))       

        # 如果两个日期都选择的话
        if whetherChooseStartDate.get() == 1 and whetherChooseEndDate.get() == 1:
            start = pd.Timestamp(datetime.date(year=startyear, month=startmonth, day=startdate))
            end = pd.Timestamp(datetime.date(year=endyear, month=endmonth, day=enddate))

        # 如果两个日期都没有选择的话
        if whetherChooseStartDate.get() == 0 and whetherChooseEndDate.get() == 0:
            start = None
            end = None

        csvDir = csvPath.get()
        filename = os.path.splitext( os.path.split(csvDir)[-1])[0]

        extDir = storePath.get() + '/' + filename + '-ext.csv'
        summaryDir = storePath.get() + '/' + filename + '-summary.csv'

        if whetherChooseRegion.get() == 1:
            regionCode = [int(item.strip()) for item in region.get(0.0, tk.END).split()]
        else:
            regionCode = None
        
        # 清空Text中的内容
        region.delete(0.0, tk.END)  

        # 使用另外一个脚本文件中的函数提取数据
        dataExtraction(csvDir, extDir, summaryDir, start, end, regionCode)

        # 提示用户已经完成数据提取
        tk.messagebox.showinfo(title='提示', message='提取完成！用时 {:.1f} s'.format(time() - startTime))


def selectCsvPath():
    csvPath.set(askopenfilename())


def selectStorePath():
    storePath.set(askdirectory())


def setStartDateRange():  
    """
    
    设置起始日期选择范围
    """
    year = int(startYear.get())
    month = int(startMonth.get())
    
    startDate['values'] = getDateRange(year, month)
    startDate.current(0)


def setEndDateRange():
    """
    
    设置终止日期选择范围
    """
    year = int(endYear.get())
    month = int(endMonth.get())

    endDate['values'] = getDateRange(year, month)
    endDate.current(0)


def getDateRange(year, month):
    """
    
    获取日期范围
    """
    bigmonth = [1, 3, 5, 7, 8, 10, 12]
    smallmonth = [4, 6, 9, 11]
    
    if month in bigmonth:
        dateRange = list(range(1, 32))
    elif month in smallmonth:
        dateRange = list(range(1, 31))
    else:
        leap = (year % 4 == 0) and not((year % 100 == 0) and (year % 400 != 0))

        if leap:
            dateRange = list(range(1, 30))
        else:
            dateRange = list(range(1, 29))
    return dateRange


def enableStartDate():
    """

    根据复选框的状态将对应的部件使能
    """
    if whetherChooseStartDate.get() is 0:
        startYear['state'] = 'disabled'
        startMonth['state'] = 'disabled'
        startDate['state'] = 'disabled'
    else:
        startYear['state'] = 'normal'
        startMonth['state'] = 'normal'
        startDate['state'] = 'normal'
        

def enableEndDate():
    """

    根据复选框的状态将对应的部件使能
    """
    if whetherChooseEndDate.get() is 0:
        endYear['state'] = 'disabled'
        endMonth['state'] = 'disabled'
        endDate['state'] = 'disabled'
    else:
        endYear['state'] = 'normal'
        endMonth['state'] = 'normal'
        endDate['state'] = 'normal'


def enabelRegion():
    """

    根据复选框的状态将对应的部件使能
    """
    if whetherChooseRegion.get() is 0:
        region['state'] = 'disable'
    else:
        region['state'] = 'normal'


# 创建主窗口
mainWindow = tk.Tk()
mainWindow.title('cdc数据提取')  # 设置主窗口名称
mainWindow.geometry('480x500')  # 设置主窗口大小
mainWindow.resizable(0, 0)  # 设置主窗口为固定大小

# 创建两个字符变量
csvPath = tk.StringVar()
storePath = tk.StringVar()

# 创建csv文件路径选择部分组件
tk.Label(mainWindow, text="目标路径:").grid(row=1, column=1)
tk.Entry(mainWindow, textvariable=csvPath, width=52).grid(row=1, column=2, columnspan=6)
tk.Button(mainWindow, text="path?", command=selectCsvPath).grid(row=1, column=8)


# 第一条分割线
ttk.Separator(mainWindow, orient=tk.HORIZONTAL).grid(row=2, column=1, columnspan=9, sticky='we')


# 创建提取文件保存路径选择部分组件
tk.Label(mainWindow, text="提取路径:").grid(row=3, column=1)
tk.Entry(mainWindow, textvariable=storePath, width=52).grid(row=3, column=2, columnspan=6)
tk.Button(mainWindow, text="path?", command=selectStorePath).grid(row=3, column=8)


# 第二条分割线
ttk.Separator(mainWindow, orient=tk.HORIZONTAL).grid(row=4, column=1, columnspan=9, sticky='we')


# 设置年月范围
years = [year for year in range(1900, 2100)]
months = [month for month in range(1, 13)]

# 设置起始年月范围使能按钮
whetherChooseStartDate = tk.IntVar(value=0)
tk.Checkbutton(mainWindow, text='选择', variable=whetherChooseStartDate, command=enableStartDate).grid(row=5, column=1)
whetherChooseEndDate = tk.IntVar(value=0)
tk.Checkbutton(mainWindow, text='选择', variable=whetherChooseEndDate, command=enableEndDate).grid(row=7, column=1)

# 创建起始日期选择部分组件
tk.Label(mainWindow, text='起始日期:').grid(row=5, column=2, pady=5)
tk.Label(mainWindow, text='年').grid(row=5, column=4)
tk.Label(mainWindow, text='月').grid(row=5, column=6)
tk.Label(mainWindow, text='日').grid(row=5, column=8)

startYear = ttk.Combobox(mainWindow, width=8)
startYear['values'] = years
startYear.grid(row=5, column=3)
startYear.current(100)
startYear['state'] = 'disable'

startMonth = ttk.Combobox(mainWindow, width=8)
startMonth['values'] = months
startMonth.grid(row=5, column=5)
startMonth.current(0)
startMonth['state'] = 'disable'

startDate = ttk.Combobox(mainWindow, width=8, postcommand=setStartDateRange)
startDate['values'] = 1
startDate.grid(row=5, column=7)
startDate.current(0)
startDate['state'] = 'disable'


# 第三条分割线
ttk.Separator(mainWindow, orient=tk.HORIZONTAL).grid(row=6, column=1, columnspan=9, sticky='we')


# 创建终止日期选择部分组件
tk.Label(mainWindow, text='终止日期:').grid(row=7, column=2, pady=5)
tk.Label(mainWindow, text='年').grid(row=7, column=4)
tk.Label(mainWindow, text='月').grid(row=7, column=6)
tk.Label(mainWindow, text='日').grid(row=7, column=8)

endYear = ttk.Combobox(mainWindow, width=8)
endYear['values'] = years
endYear.grid(row=7, column=3)
endYear.current(118)
endYear['state'] = 'disable'

endMonth = ttk.Combobox(mainWindow, width=8)
endMonth['values'] = months
endMonth.grid(row=7, column=5)
endMonth.current(0)
endMonth['state'] = 'disable'

endDate = ttk.Combobox(mainWindow, width=8, postcommand=setEndDateRange)
endDate['values'] = 1
endDate.grid(row=7, column=7)
endDate.current(0)
endDate['state'] = 'disable'


# 第四条分割线
ttk.Separator(mainWindow, orient=tk.HORIZONTAL).grid(row=8, column=1, columnspan=9, sticky='we')


# 创建地区编码输入部分组件
whetherChooseRegion = tk.IntVar(value=0)
tk.Checkbutton(mainWindow, text='选择', variable=whetherChooseRegion, command=enabelRegion).grid(row=9, column=1)
tk.Label(mainWindow, text='地区编码：').grid(row=9, column=2)
region = tk.Text(mainWindow, width=50)
region.grid(row=9, column=3, columnspan=6, pady=5)
region['state'] = 'disable'


# 第五条分割线
ttk.Separator(mainWindow, orient=tk.HORIZONTAL).grid(row=10, column=1, columnspan=9, sticky='we')

# 创建一条垂直分割线
ttk.Separator(mainWindow, orient=tk.VERTICAL).grid(row=5, rowspan=5, column=2, sticky='wns')


# 创建数据提取按钮
dataExtract = tk.Button(mainWindow, width=20, text='开始提取', relief='groove', command=getData)
dataExtract.grid(row=11, column=3, columnspan=3, pady=5)


# 开启主窗口事件循环
mainWindow.mainloop()