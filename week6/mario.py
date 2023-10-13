while True:
  try:
    height = int(input("Height:"))

    if 0 < height and height < 9:
      break
    else:
      print("Please enter a number 1 to 8")

  except:
    print("Please enter a number 1 to 8")

for i in range(height):
  space = height - 1 - i
  hash_count = i + 1

  # ピラミッドの頂点を示すための空白を出力
  print((" ") * space, end="")

  # ピラミッド部分を出力
  print(("#") * hash_count, end="")
  print("  ", end="")
  print(("#") * hash_count)