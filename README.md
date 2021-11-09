# Ketenpere
-----------
It is a command line tool that prints the struct layout.

##Why?
Because sometimes you want to do things that don't fit into the normal way of doing it.

##Example

Example with [test2.ke](https://github.com/volkanunal/ketenpere/blob/master/test2.ke)

```c
struct ketenpere {
    int ket;
    int en;
    int pere;

    struct lafargue {
        double laf;
        float ar;
        char* gue;

        struct jxb {
            int* yohhya;
        };
    };    
};
```

```
./ketenpere.out test2.ke
```

```
ketenpere(struct) has following member or members (int)ket (int)en (int)pere (struct)lafargue
lafargue(struct) has following member or members (double)laf (float)ar (char*)gue (struct)jxb
jxb(struct) has following member or members (int*)yohhya 
```


##Task Lists


- [ ] Fix some bugs (if more than one nested struct)
- [ ] Add support user-defined type as pointer
- [ ] Add support for union token
- [ ] Add support for enum token
- [ ] Add doc








