# lab03 HTML CSS Selector

## 目的

- 1.复习巩固线性表、栈等数据结构。

- 2.练习使用树相关数据结构。

- 3.熟悉和了解在实际问题中合理设计和使用数据结构。

- 4.训练学生阅读和理解课外资料的能力。

## 问题描述

  HTML CSS Selector是浏览器支撑Javascript脚本执行的核心和基础组建，也是众多互联网数据采集软件（如Scrapy）都支持的查询和数据抽取方式。只有熟悉和了解常用的数据结构，尤其是树，才能实现一个功能正确、方便易用的HTML CSS Selector。此次实验，希望学生能够一方面通过这个任务巩固数据结构知识，同时也基于数据结构开发未来自己能够使用的工具。

### 具体问题：

- 1.通过树数据结构对HTML DOM层次结构进行建模。
- 2.实现常用HTML CSS Selector以及对应的获取文本、HTML、链接等操作。
- 3.开发测试或者演示程序，展示HTML CSS Selector的使用方法，验证正确性。

### 步骤

- 1 .读入HTML代码文件或给定一个网址，通过树数据结构存储该HTML页面内容。

- 2.阅读理解CSS选择器的定义和功能，参考：
  
  > a)易懂入门资料：https://www.w3school.com.cn/cssref/css_selectors.asp
  > 
  > b)CSS选择器国际标准：https://www.w3.org/TR/selectors/ 
  > 
  > c)其他工具如Scrapy中的CSS选择器：https://www.educba.com/scrapy-css-selector/；
  > https://docs.scrapy.org/en/latest/topics/selectors.html。
  > Beautiful Soup: https://www.crummy.com/software/BeautifulSoup/bs4/doc/等
  > 
  > d)其他相关资料

- 3.实现基本CSS选择器（请见下表），例如：
  
  - a)*,所有元素
  - b)ID Selector，例如： #myId
  - c)Class Selector，例如： .myClass
  - d)Tag Selector，例如： DIV
  - e)空格选择器，例如 selectorA selectorB， DIV .myClass等。
    设计查询函数调用上述选择器，返回满足条件的elements/node的集合

- 4.对于选择器返回的每个element/node，支持以下操作：
  
  - a)获取其innerText
  - b)获取该node的整个outerHTML
  - c)对于A标签，支持获取其包含的链接href的值
  - d)支持对返回的element再次调用选择器进行查询。例如，先通过一个选择器获取到一个新闻列表中的每一条新闻所在的节点，然后在每个节点上执行查询，分别抽取其中的标题、链接、日期等。
  - e)这些操作可以实现成函数，也可直接嵌入到选择器中，例如scrapy中的::text, ::attr(‘href’)

- 5.开发测试或者演示程序，展示HTML CSS Selector的使用方法，验证正确性，演示方式和过程可参考Scrapy中Response.css的使用方法。


