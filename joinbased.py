import itertools
import copy
import math
import numpy as np
import matplotlib.pyplot as plt

def get_count_ET(E,ET):
    count = {}
    for i in ET:
        count[i] = 0
        for j in E:
            if j[0] == i:
                count[i] += 1
    return count
def get_canyudu(P,count_ET):
    canyudu = 1 #设置一个最大参与率
    for key in P.keys():
        canyulv = P[key]/count_ET[key]
        if canyulv < canyudu: #这里判断用于返回最下参与率
            canyudu = canyulv
    return canyudu
def createT2(E,R):
    T2 = []
    E_len = len(E)
    for i in range(E_len-1):
        for j in range(i,E_len):
            if E[i][0]!=E[j][0] and isNiber(E[i],E[j],R):
                instance = []
                instance.append(E[i][0]+','+str(E[i][1]))
                instance.append(E[j][0]+','+str(E[j][1]))
                T2.append(instance)
    T_dic = Table_2_Tdic(T2)
    return T_dic
def Table_2_Tdic(T):
    table = {}
    for l in T:
        co = ""
        row_instance = []
        l_len = len(l)
        for i in range(l_len):
            if i != l_len-1:
                co += str(l[i]).split(',')[0] + ','
            else:
                co += str(l[i]).split(',')[0]
            row_instance.append(str(l[i]))
        if str(co) not in table.keys():
            table[str(co)] = [row_instance]
        else:
            table[str(co)].append(row_instance)
    # print(table)
    return table
def T_2_Tk(T,k):
    T_list = []
    keys = list(T.keys())
    keys.sort()
    keys_len = len(keys)
    for i in range(keys_len-1):
        if keys[i].split(',')[:-1] != keys[i+1].split(',')[:-1]:
            continue
        for j in range(i+1,keys_len):
            if keys[j].split(',')[:-1] == keys[i].split(',')[:-1]:
                for instance_i in T[keys[i]]:
                    for instance_j in T[keys[j]]:
                        if instance_i[:-1] == instance_j[:-1]:
                            tem = []
                            tem.extend(instance_i)
                            tem.append(instance_j[-1])
                            T_list.append(tem)
            else:
                break
    Tk = T_list.copy()
    for C_Tlist in T_list:
        for c in itertools.combinations(C_Tlist, k-1):
            c = list(c)
            c_len = len(c)
            co = ""
            row_list = []
            for i in range(c_len):
                if i != c_len-1:
                    co += c[i].split(",")[0]+','
                else:
                    co += c[i].split(",")[0]
                row_list.append(c[i])
            if co not in T.keys() or row_list not in T[co]:
                Tk.remove(C_Tlist)
                break
    T_dic = Table_2_Tdic(Tk)
    return T_dic
def Tk_2_Pk(T_dic, count_ET, min_prev):
    Pk = []
    T = {}
    keys = list(T_dic.keys())
    keys.sort()
    for key in keys:
        key_list = key.split(",")
        p = {}
        key_len = len(key_list)
        for i in range(key_len):
            p[key_list[i]] = len(set([wai[i] for wai in T_dic[key]]))
        canyudu = get_canyudu(p, count_ET)
        if canyudu >= min_prev:
            T[key] = T_dic[key]
            Pk.append(key_list)
    return T, Pk
def P_2_Ck(P):
    C = []
    p_len = len(P)
    for i in range(p_len):
        for j in range(i+1,p_len):
            if P[j][:-1] == P[i][:-1]:
                temp = []
                temp.extend(P[i])
                temp.append(P[j][-1])
                C.append(temp)
    return C
if __name__ == '__main__':
    min_prev = 0.3  # 最小参与率
   	ET = ["A", "B", "C", "D"]
    E = [["A", 1, [24, 14]]
        , ["A", 2, [64, 44]]
        , ["A", 3, [46, 24]]
        , ["A", 4, [63, 7]]
        , ["B", 1, [13, 3]]
        , ["B", 2, [19, 45]]
        , ["B", 3, [47.5, 10.5]]
        , ["B", 4, [62, 52]]
        , ["B", 5, [13, 50]]
        , ["C", 1, [39, 11]]
        , ["C", 2, [52, 50]]
        , ["C", 3, [40, 36]]
        , ["D", 1, [40, 20]]
        , ["D", 2, [6, 10]]]
    R = 16  # 设最小邻近关系的距离为16
    # drawData(E, R)
    count_ET = get_count_ET(E, ET)
    k = 2
    T_C = createT2(E, R)
    C = list(T_C.keys())
    C.sort()
    print("C2")
    print(C)
    T, P = Tk_2_Pk(T_C, count_ET, min_prev)
    print("T2")
    for i in T.keys():
        print(i, T[i])
    print("P2")
    print(P)
    while (1):
        k += 1
        C = P_2_Ck(P)
        if len(C) == 0:
            break
        print("C{}".format(k))
        print(C)
        T_C = T_2_Tk(T, k)
        T, P = Tk_2_Pk(T_C, count_ET, min_prev)
        if bool(T):
            print("T{}".format(k))
            for i in T:
                print(i, T[i])
        if bool(P):
            print("P{}".format(k))
            print(P)
