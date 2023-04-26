num = 20812168509434597367146703229805575690060615791308155437936410982393987532344  # 256-bit整数

# 32ビットずつ8つに分割
parts = []
for i in range(10):
    part = (num >> (i * 32)) & 0xffffffff
    parts.append(part)

# 16進数文字列に変換して出力
for part in parts:
    print(hex(part))