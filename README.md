# Evaluate

目录
```

│  .gitattributes
│  README.md
│
├─Evaluate
│  ├─evaluate
│  │      cmd.sh
│  │      evaluate
│  │      evaluate.c
│  │
│  ├─models
│  │      group.c
│  │      group.h
│  │      process.c
│  │      process.h
│  │      submission.c
│  │      submission.h
│  │
│  ├─run
│  │      .cmd.sh.swp
│  │      cmd.sh
│  │      run
│  │      run.c
│  │      run.out
│  │
│  └─utils
│          filepath.c
│          filepath.h
│          results.h
│          str.c
│          str.h
│
└─test
    │  test_program
    │
    └─helloworld
            test_program.c
            test_program_00001.ans
            test_program_00001.in
            test_program_00001.out
            test_program_00002.ans
            test_program_00002.in
            test_program_00002.out
=======
├─Evaluate
│  ├─evaluate（总评测机）
│  ├─models（模型）
│  ├─run（组例评测机）
│  └─utils（工具）
└─test
    └─helloworld
```

支持语言：

> 当前支持c/cpp(可执行程序均可)/python/python3/java，
>
> 需要预装gcc, java, python2, python3（安装python3后建立链接到/usr/bin/python3）

如何使用:

```
./evaluate limit_time limit_memory len_of_ans data_path program_path type
eg1.
./evaluate 1000 256 2 /home/jeffxie/Documents/test/helloworld/ /home/jeffxie/Documents/test/test_program cpp
eg2.
./evaluate 1000 256 2 /home/jeffxie/Documents/test/helloworld/ /home/jeffxie/Documents/test/test_program.py python
```

五种type：

> c/cpp/python/python3/java



input文件名：

```
program_name_%05d.in
eg.
test_program_00001.in
test_program.py_00001.in
```

ans文件名：
```
program_name_%05d.ans
eg.
test_program_00001.ans
test_program.py_00001.ans
```


原理：

> run实现对每个in输出的ans和out对拍，evaluate通过调用run实现整个problem的评测。

接下来做什么：

> 接下来用其他编程语言实现一个socket服务器，并存放在docker容器中。该服务器实现接收problem的信息，检测代码的安全性，程序的编译，写入in和ans文件并设置文件权限，调用该评测机对拍output和answer，删除评测数据，再返回结果，以及多个评测机的调度。

socket服务器使用该评测机安全性建议：

> 先进行安全性限制，部分函数库不得使用，检测到就拒绝代码
>
> 置于容器中
>
> in/ans文件权限设置为744，防止未知写入。
>
> socket服务器程序设置权限为711，并和程序分离
>
> 降低socket服务器和评测机的执行用户权限。
>
> 加密出两个文件夹名，将in/ans的数据文件和程序分别放在其中，防止程序对数据文件的改动。
>
> 加密程序名
