# 线性表
在关注于线性表前，我们先来看几个宏观概念。
## 0.1 Abstract data type
>A **mathematical model** for data types, a **theoretical concept**.
>
>Defined by its behavior (semantics) from the point of view of a user, specifically in terms of possible **data**, **the relationship between data**, possible **operations** on data of this type, and the behavior of these operations.
>
>Contrasting with data structures, which are concrete representations of data, and are the point of view of an implementer, not a user.
>
>其可视为数据结构的**logic form**部分

## 0.2 数据结构
>可见，数据结构 **based on** the **physical structure and ability** of a computer to fetch and store data at any place in its memory, implements the **physical form** of the ADT.
>
>- 通常用位串bits表示出数据
>- 用顺序存储结构(直接利用存储地址的相对位置)或链式存储结构(借助指向存储地址的指针)表示出数据之间的逻辑关系
>- Based on specification(规范)，implement operations by algorithms
### 0.2.1 算法 Algorithm
> A **finite sequence of rigorous instructions**, used as specifications for performing calculations and data processing.
### 0.2.2 算法分析入门
通常，从算法中选取出基于研究的问题的基本操作，对算法各基本操作的重复执行次数求和得到频度f(n)，作为算法的时间复杂度的度量；

但实际中，我们所关心的通常是一个算法所花时间的数量级，我们取*不包括这个函数的低阶项和首项系数的**最大频度数量级:***
$$maxlevel(f(n))$$

使用最大频度数量级度量时间复杂度时，用大O符号表述，时间复杂度$T(n)$表示为
$$T(n)=O( maxlevel(f(n))$$
其考察当输入值大小趋近无穷时的情况，可被称为是**渐近的**。
***

## 1.1 线性表的ADT
>线性表是由某类elemtype的数据元素(数据的基本单位)构成的有限**序列**。
>
>$D = \{ a_i | a_i ∈ElemSet，i = 1, 2, …, n \}$
>
>$R = \{ < a_i-1, a_i > | a_i-1, a_i  ∈ D ，i = 1, 2, …, n\}$
>
>初始化、清除与基本判断：初始化创建、销毁/清空、获得长度、判断是否为空
>
>更改：变值、插入、删除 
>
>遍历：获得前驱/后继数据元素、遍历
>
>索引：按值索引、按位置索引
## 1.2 实现线性表的数据结构
### 1.2.1 第一种是顺序表
即表示线性关系的方式是直接利用内存中连续存储时的相对物理位置。

因为是连续的，顺序中的任意数据元素都可**随机快速存取**，因此，对顺序表的遍历与索引都是极其高效的。但受限于需要顺序存储，插入和删除数据元素些许复杂。 
- 但这种存取需要用一个定义最长可存取范围的变量`listsize`限制并表示顺序表的范围。因此，初始化分配内存时，需要指定一个`list_init_size`,分配空间大小为：`list_init_size*sizeof(ElemType)`。而后，若达到了`list_init_size`的限制，则需重新分配一块新内存空间，若希望每次扩容都增加定长，则为`(L.listsize+list_step_size)*sizeof(ElemType))`
- 出于高效考虑，我们再定义变量`length`来表示表中当前存储的元素个数。

- 我们用指向所分配空间的初地址的*elemtype*类型的指针`elem`来取地址及地址中的数据元素。
```c
typedef struct SqList{
        ElemType* elem;
        int length;
        int listsize;
    }SqList;
```
至此，我们表示好了顺序表的数据元素及之间的关系，还需用一定的算法实现线性表ADT中的operations。在此提出几点需要注意的：
- 初始化分配内存时候**判断是否分配成功！**
- 插入新元素时**判断顺序表是否已满**
- 判断**索引是否合法**
  
### 1.2.2 第二种是链表
即表示线性关系的方式是依次为每一个数据元素添加指向下一个元素地址的指针；这两者共同组成一个个结点，也即链表本身的数据结构类型(其本身是指向Node类型的指针，其值为最前面节点的地址，一个个这样类型的指针串起来构成整个链表)：
```c
typedef struct Node{
    Elemtype data;
    Node* next;
}Node, *LinkedList;
```
由于数据元素在内存中的不是连续存储，不能实现快速的随机存取。但在插入与删除时由于不需要拘泥于“连续”，只需要调动较少位置的指针即可完成链表的更改。其中需要注意的是，在插入元素时，需要先给待插入节点的next赋值，再由指向插入位置的上一个节点的next改为指向新节点，从而避免内存泄漏。

另外，为了实现在最前面的位置插入数据元素与在其他位置插入的操作统一，以及为维护链表起始处的指针不变动，我们设置**头节点**，存放空data，其next指向第一个数据元素。

### 实际上，上述链表为`单链表`,指只定义了指向下一个节点的指针的链表；若同时再定义指向前一个节点的指针，则为`双向链表`，若在单链表的基础上再定义由尾节点指向第一个数据元素所在节点的指针，则构成`循环链表`，若依靠指针实现，但存储形式仍是连续的内存空间，则为`静态链表`。