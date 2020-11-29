from matplotlib import pyplot as plt
import threading

plt.rcParams['font.sans-serif'] = ['KaiTi']
plt.rcParams['axes.unicode_minus'] = False

def cal(ph, ls, ln):
    phs0 = ln * ph / ((ln - 1) * ph + 1)
    phs1 = ls * ph / ((ls - 1) * ph + 1)
    return (phs0, phs1)

def draw(pe, ph, phs0, phs1):
    x = [0,pe,1]
    y = [phs0, ph, phs1]
    plt.title("P(H|S)与P(E|S)关系图") 
    plt.xlabel("P(E|S)") 
    plt.ylabel("P(H|S)")
    plt.plot(x,y) 
    plt.show()

def phs(pe, ph, phs0, phs1, pes):
    if pes<0 or pes>1:
        return "Wrong P(E|S)!"
    if pes<pe:
        return phs0 + pes*((ph-phs0)/pe)
    else:
        return ph + (pes-pe)*((phs1-ph)/(1-pe))

if __name__ == "__main__":
    pe=float(input("请输入:\nP(E) = "))
    ph=float(input("P(H) = "))
    ls=float(input("LS = "))
    ln=float(input("LN = "))
    (phs0, phs1) = cal(ph, ls, ln)
    print("画图中...\n")
    t = threading.Thread(target=draw, args=(pe, ph, phs0, phs1))
    t.start()
    # draw(pe, ph, phs0, phs1)
    while True:
        i = input("\n请输入P(E|S) = ")
        if i in ("q", "Q"):
            break
        pes = float(i)
        print("P(H|S) =", phs(pe, ph, phs0, phs1, pes))
