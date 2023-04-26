parts = [2651602770, 1293512037, 25596166, 688299708, 3268658772, 2255362604, 3029427677, 718133515]  # 32ビットの10進数の整数8つ

# 8つの32ビット整数を256ビット整数に変換
num = 0
for i, part in enumerate(parts):
    num += part << (i * 32)

print(hex(num))
print(num)