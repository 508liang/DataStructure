# Lab2 Html Parser
## 判断合法性
遍历整个seqList

遇到<加字符
- 从该字符开始读取，直到空格或者> 获得tag对应token
- push tag into stack

遇到<加/
- 从/后开始读取，直到> 获取对应token
- 检查是否和pop出来的tag的token一致，不一致，则return不合法；一致，则继续执行循环
- 直到循环结束，最后stack为空，合法

## OutHTML
遍历seqList, 同时遍历给定path

遇到<加字符

检查是否和给定path的当前位一致，若一致，path到下一位，继续遍历；若一致且到了path的末位，则输出当前<直到</>

若不一致，仍然push，但path标记为lock,pop出这个后再解除lock

遇到<加/

pop

