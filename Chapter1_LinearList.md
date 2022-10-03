# 线性表
在关注于线性表前，我们先来看几个宏观概念。
## Abstract data type
>A **mathematical model** for data types, a **theoretical concept**.
>
>Defined by its behavior (semantics) from the point of view of a user, specifically in terms of possible **data**, **the relationship between data**, possible **operations** on data of this type, and the behavior of these operations.
>
>Contrasting with data structures, which are concrete representations of data, and are the point of view of an implementer, not a user.
>
>其可视为数据结构的**logic form**部分

## 数据结构
>可见，数据结构 **based on** the **physical structure and ability** of a computer to fetch and store data at any place in its memory, implements the **physical form** of the ADT.
>
>- 通常用位串bits表示出数据
>- 用顺序存储结构(直接利用存储地址的相对位置)或链式存储结构(借助指向存储地址的指针)表示出数据之间的逻辑关系
>- Based on specification(规范)，implement operations by algorithms
### 算法 Algorithm
> A **finite sequence of rigorous instructions**, used as specifications for performing calculations and data processing.
#### 算法分析入门
通常，从算法中选取出基于研究的问题的基本操作，对算法各基本操作的重复执行次数求和得到频度f(n)，作为算法的时间复杂度的度量；

但实际中，我们所关心的通常是一个算法所花时间的数量级，我们取*不包括这个函数的低阶项和首项系数的**最大频度数量级:***
$$maxlevel(f(n))$$

使用最大频度数量级度量时间复杂度时，用大O符号表述，时间复杂度$T(n)$表示为
$$T(n)=O( maxlevel(f(n))$$
其考察当输入值大小趋近无穷时的情况，可被称为是**渐近的**。
***

## 线性表的ADT
>线性表是由某类elemtype的数据元素(数据的基本单位)构成的有限**序列**。
>
>$D = \{ a_i | a_i ∈ElemSet，i = 1, 2, …, n \}$
>
>$R = \{ < a_i-1, a_i > | a_i-1, a_i  ∈ D ，i = 1, 2, …, n\}$
>
>初始化创建、销毁/清空、获得长度、判断是否为空
>
>更改、插入、删除 
>
>获得前驱/后继数据元素、遍历
>
>按值索引、按位置索引
## 实现线性表的数据结构
### 第一种是顺序表
即表示线性关系的方式是直接利用内存中连续存储时的相对物理位置。

其所占空间为
```c 