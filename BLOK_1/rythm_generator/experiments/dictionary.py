list = []

def create_dictionary(first, second, third):
    return {
        "first": first,
        "second": second,
        "third": third
    }

for i in range(0, 5):
    dictionary1 = create_dictionary(i*1, i*2, i*3)
    list.append(dictionary1)

print(list)
