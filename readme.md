## user-interface 本文件夹下的程序为单片机上的程序,目标是发展成智能家居大项目中各传感器的模块代码
### learn note
1.系统移植的四大步骤  http://www.cnblogs.com/jiangzhaowei/p/6136879.html
2.typescript  https://www.w3cschool.cn/typescript/typescript_basic_syntax.html
### git提交代码到github  
教程参考 http://blog.csdn.net/kongying19910218/article/details/50515834
一般先在github建立我们的仓库并获得url https://github.com/GreenOrangeTechnology/development-board-project.git ;
然后进到我们待提交目录下git init;接着可以(或者下两步)git status查看当前目录状态;接着git add . 将本地文件添加进本地历史库;接着git commit -m "这里是注释。。。";接着 git remote add origin https://github.com/chenyufeng1991/NewsClient.git  /*可省略   git pull origin master
该命令是先把github上的文件拉下来，注意在每次提交之前要首先进行pull，这是防止冲突；执行以后可能会出现如下界面，其实不用管，输入“:wq”回车键退出即可；*/;接着git push -u origin master这一步是真正向github提交，执行完成后，github上的repository就有和你本地一样的代码文件
