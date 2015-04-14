def factorial(number):
	product = 1
	while number > 0:
		product *= number
		number -= 1
	print(product)

number = int(input("Enter n for n!: "))
factorial(number)
