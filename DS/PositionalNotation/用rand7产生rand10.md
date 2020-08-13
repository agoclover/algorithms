# 用 rand7 产生 rand10

[Lintcode1496](https://www.lintcode.com/problem/implement-rand10-using-rand7/description?utm_source=sc-zhihuzl-lm)



> 已有方法 rand7 可生成 1 到 7 范围内的均匀随机整数, 试写一个方法 rand10 生成 1 到 10 范围内的均匀随机整数.
>
> 注意: 
>
> 1. 不要使用系统的 Math.random() 方法;
> 2. rand7 已定义;
> 3. 传入参数: n 表示 rand10 的调用次数.



在此之前, 先考虑另一种简单的情况: 用 rand10 产生 rand7.



这个题目非常简单, 用 rand10 随机生成一个 $x\in 1, 2, ... 10$, 如果这个数是 8, 9, 10, 就不要重新取, 也就是只有 $x\in 1, 2, ... 7$ 就返回. 代码如下:

```java
public class Solution extends SolBase{
    public  int rand7() {
        while(true){
            int res = rand10();
            if(res <= 7) {
                return res;
            }
        }
    }
}
```

再考虑用 rand25 生成 rand7, 这时候把 7 以上直接截去, 效率就太低了, 很容易想到截去 21 以上的, 然后剩下 $x\in 1, 2, ... 21$, 这个数对 7 取模再加 1 即可:

```java
public class Solution extends SolBase{
    public  int rand7() {
        while(true){
            int res = rand25();
            if(res <= 21) {
                return (res % 7) + 1;
            }
        }
    }
}
```

以上是 rand大 生成 rand小, 那么再考虑 rand小 生成 rand大 就很容易了. 小生成大难点在于, 一次随机只能产生一个小范围的数, 比如 rand7, 得到最大也就 7, 那么肯定取不到 10.

所以一次取不到, 就想办法取两次呗. **利用进制思想**, 第一次随机的数减 1 作为 7 进制两位数的第二位, 第二次取的数减一作为 7 进制两位数的个位, **就实现扩大随机数范围的效果了**.

比如 7 进制两位数最大是 $6\times 7 + 6 = 48$ , 即 $0, 1, 2, ..., 48$, 接着去掉 40及以上, 然后再对 10 取模再加 1 即可. 算法如下:

```java
public class Solution extends SolBase{
    public  int rand10() {
        while(true){
           int res = (rand7() - 1) * 7 + rand7() - 1;
            if(res <= 39) {
                return res % 10 + 1;
            }
        }
    }
}
```

但有人会想, 我直接 rand7 + rand7, 不也是能取到 1 到 14 吗? 为何要这么麻烦. 注意, 这里其实就是概率论里面最基础的二元随机变量的概率密度函数, 必须保证 1 到 14 每个数的概率是相同的,  例如生成 0 的方式只有 $(0, 0)$, $P_0=1/49$, 但 1 有 $(1, 0), (0, 1)$ 两种, $P_1=2/49$, 显然 rand7 + rand7 不能产生等密度的数.