from functools import reduce

# Example Huffman coding implementation
# Distributions are represented as dictionaries of { 'symbol': probability }
# Codes are dictionaries too: { 'symbol': 'codeword' }

def huffman(p):
	'''Return a Huffman code for an ensemble with distribution p.'''
	#assert(sum(p.values()) == 1.0) # Ensure probabilities sum to 1

	# Base case of only two symbols, assign 0 or 1 arbitrarily
	if(len(p) == 2):
		return dict(zip(p.keys(), ['0', '1']))

	# Create a new distribution by merging lowest prob. pair
	p_prime = p.copy()
	a1, a2 = lowest_prob_pair(p)
	p1, p2 = p_prime.pop(a1), p_prime.pop(a2)
	p_prime[a1 + a2] = p1 + p2

	# Recurse and construct code on new distribution
	c = huffman(p_prime)
	ca1a2 = c.pop(a1 + a2)
	c[a1], c[a2] = ca1a2 + '0', ca1a2 + '1'

	return c

def lowest_prob_pair(p):
	sorted_p = sorted(p.items(), key=lambda x: x[1])
	return sorted_p[0][0], sorted_p[1][0]

def Huffman_Find(code,seq,i=0):
	if len(seq) == i: return code
	else: return Huffman_Find(dict(filter(lambda x: x[1][i] == seq[i], code.items())), seq, i+1)

def Huffman_Encode(archive, code):
	with open('BAK_'+archive,'wb') as file:
		text = ''
		bin_conv = lambda text: map(lambda x:int(x,2), [text[i*8:(i+1)*8] for i in range((len(text)+8-1)//8)]) #Quebra de 8 em 8 e codifica os bytes
		for elem in list(open(archive, 'r').read()):
			text += code[elem]
		file.write(bytes(bin_conv(text)))
		file.close()

def Huffman_Decode(archive,code):
	with open('BAK_'+archive,'rb') as file:
		
		text = ""
		byte = file.read(1)
		while(byte != b''):
			try:
				byte = ord(byte)
				text += bin(byte)[2:].rjust(8, '0')
				#print(text)
				byte = file.read(1)
			except:
				pass
		decoder = lambda text,code,x,y: list(filter(lambda elem: len(elem)==1,(Huffman_Find(code,text[x:-len(text)+i]) for i in range(x,y))))
		max_len_code = lambda code: len(code[sorted(code, key=lambda x: len(code[x]))[-1]])
		#print(decoder(text, code, 11, 16))
		print(text)
		i = 0
		j = 0
		while i <= len(text):
			while j <= len(text):
				if decoder(text,code,i,j) != []:
					print(decoder(text,code,i,j))
					#print(i,j)
					i = j-1
					#print(i,j)
					if i >= len(text): break
				j+=1
			i+=1
		


if __name__=="__main__":
	with open('teste1.txt','r') as file:
		archive = list(file.read())
		characters = set(map(lambda x: (x,archive.count(x)), archive)) #Counting
		frequency = {}
		list(map(lambda x: frequency.update({x[0]:x[1]/len(archive)}), characters))
		code = huffman(frequency)
		Huffman_Encode("teste1.txt",code)
		Huffman_Decode("teste1.txt",code)
		print("Codigo: ",code)
