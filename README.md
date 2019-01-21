# Evaluate

目录
```
├─Evaluate
│  ├─evaluate（总评测机）
│  ├─models（模型）
│  ├─run（组例评测机）
│  └─utils（工具）
└─test
    └─helloworld
```

如何使用:
```
./evaluate limit_time limit_memory len_of_ans data_path program_path program_name
eg.
./evaluate 1 256 2 /home/jeffxie/Documents/test/helloworld/ /home/jeffxie/Documents/test/test_program test_program
```

输入文件名：
```program_name_%05d.in```
答案文件名：
```program_name_%05d.ans```

原理：
> run实现对每个in输出的ans和out对拍，evaluate通过调用run实现整个problem的评测。

接下来做什么：
接下来可以用其他编程语言实现一个socket服务器，该服务器实现接收problem的信息，程序的编译，写入in和ans文件并设置文件权限，调用该评测机对拍output和answer，删除评测数据，再返回结果，以及最重要的多评测机的调度，。
