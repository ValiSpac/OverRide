str_encrypt = "Congratulations!"
str_decrypt = "Q}|u`sfg~sf{}|a3"
counter = 21

while counter != 0:
    tmp = ''.join(chr(ord(c) ^ counter) for c in str_encrypt)
    if tmp == str_decrypt:
        print(f"Found it, it is : {counter}")
        break
    counter -= 1
