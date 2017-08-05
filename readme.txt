（关于XSB格式由来，可参阅本站博文《XSokoban》最后三段） 
推箱子关卡一般用XSB格式来保存和交流：(In Sokoban community, levels are shared in a standard format called XSB)

字符     含义
@   ==> 人 (man)
+   ==> 人在目标点 (man on goal)
$   ==> 箱子 (box)
*   ==> 箱子在目标点 (box on goal)
#   ==> 墙 (wall)
.   ==> 目标点 (goal)
-   ==> XSB格式空格代表“地板”，又因为连续多个空格在网页或即时通讯软件中偶尔显示有问题，
        也用“-”或“_”代替空格。(floor, represented by ' ' or '-' or '_')

例子 (example)
----#####----------
----#---#----------
----#$--#----------
--###--$##---------
--#--$-$-#---------
###-#-##-#---######
#---#-##-#####--..#
#-$--$----------..#
#####-###-#@##--..#
----#-----#########
----#######--------
Title: Classic level 1
Author: Thinking Rabbit

上面的XSB格式关卡就是下面的图片关卡
Below is the image of the above XSB level



这是答案:
(This is the solution in LURD format, l=left, u=up, etc. Uppercase letters stand for pushes.)
ullluuuLUllDlldddrRRRRRRRRRRdrUllllllluuululldDDuu
lldddrRRRRRRRRRRRRlllllllluuulLulDDDuulldddrRRRRRR
RRRRRllllllluuulluuurDDuullDDDDDuulldddrRRRRRRRRRR
uRRlDllllllluuuLLulDDDuulldddrRRRRRRRRRRdRRlUlllll
lllllllulldRRRRRRRRRRRRRuRDldR

答案是LURD格式。
l 或 L ==> 左
r 或 R ==> 右
u 或 U ==> 上
d 或 D ==> 下

小写字母是移动， 大写字母是推动。
