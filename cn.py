def binconv(data):
    return ''.join(format(ord(i), '08b') for i in data)

def crccal(data_bits, poly, crc_size):
    rem = list(data_bits + ('0' * crc_size))

    for i in range(len(data_bits)):
        if rem[i] == '1':
            for j, p in enumerate(poly):
                rem[i + j] = str(int(rem[i + j]) ^ int(p))

    return ''.join(rem[-crc_size:])

def crcver(received, poly):
    rem = list(received)
    poly_len = len(poly)

    for i in range(len(received) - len(poly) + 1):
        if rem[i] == '1':
            for j, p in enumerate(poly):
                rem[i + j] = str(int(rem[i + j]) ^ int(p))

    return ''.join(rem[-(poly_len - 1):])


data = input("Enter the data : ")

data_bits = binconv(data)

print("\nOriginal data : ", data)
print("Original Binary data is : ", data_bits)

poly = "1100000001111"
crc_size = 12

crcval = crccal(data_bits, poly, crc_size)

print("CRC value : ", crcval)

transmitted = data_bits + crcval

print("Finally transmitted data : ", transmitted)

remainder = crcver(transmitted, poly)

print("\nReceiver remainder : ", remainder)

if int(remainder, 2) == 0:
    print("No error in transmitted data")
else:
    print("Error detected")


corrupted = list(transmitted)

if corrupted[0] == '0':
    corrupted[0] = '1'
else:
    corrupted[0] = '0'

corrupted = ''.join(corrupted)

print("\nCorrupted transmitted data : ", corrupted)

corrupted_remainder = crcver(corrupted, poly)

print("Corrupted data remainder : ", corrupted_remainder)

if int(corrupted_remainder, 2) == 0:
    print("No error detected")
else:
    print("Error detected")
