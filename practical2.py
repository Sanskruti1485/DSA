MAX = 10  # Define maximum size for the hash table

class WOChain:
    def __init__(self):
        self.a = [[-1, -1] for _ in range(MAX)]  # Initialize the hash table with -1

    def hash_key(self, num):
        return num % MAX

    def chain(self, key, num):
        flag = False
        count = sum(1 for i in self.a if i[0] != -1)  # Count filled slots

        if count == MAX:
            print("\nHash Table Is Full")
            self.display()
            exit(1)

        if self.a[key][0] == -1:
            self.a[key][0] = num
        else:
            ch = self.a[key][1]  # Get the chain index
            if ch == -1:
                # Try from key+1 to end
                for i in range(key + 1, MAX):
                    if self.a[i][0] == -1:
                        self.a[i][0] = num
                        self.a[key][1] = i
                        flag = True
                        break
                # If not found, try from 0 to key-1
                if not flag:
                    for i in range(0, key):
                        if self.a[i][0] == -1:
                            self.a[i][0] = num
                            self.a[key][1] = i
                            flag = True
                            break
            else:
                # Traverse the chain
                while self.a[ch][1] != -1:
                    ch = self.a[ch][1]
                for i in range(ch + 1, MAX):
                    if self.a[i][0] == -1:
                        self.a[i][0] = num
                        self.a[ch][1] = i
                        flag = True
                        break
                if not flag:
                    for i in range(0, ch):
                        if self.a[i][0] == -1:
                            self.a[i][0] = num
                            self.a[ch][1] = i
                            flag = True
                            break

    def display(self):
        print("\nThe Hash Table is...")
        print(" Index | Value | Chain")
        print("------------------------")
        for i in range(MAX):
            print(f"   {i:2}   |  {self.a[i][0]:3}  |  {self.a[i][1]:3}")

def main():
    h = WOChain()

    try:
        n = int(input("\nEnter the number of elements to insert into the hash table: "))
        if n > MAX:
            print("Cannot insert more than 10 elements. Hash table size = 10.")
            return

        for _ in range(n):
            num = int(input("Enter the number: "))
            key = h.hash_key(num)
            h.chain(key, num)

        h.display()
    except ValueError:
        print("Please enter valid integers.")

if __name__ == "__main__":
    main()
