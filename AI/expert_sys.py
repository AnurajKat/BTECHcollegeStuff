import sys,argparse, csv, copy

metals = []

def knowledge_base():
    global metals
    reader = csv.reader(open('metals.csv'))
    key=('name','density','magnetic','colour','melting_point','type')
    metal_dictionary=[]
    i=0
    for row in reader:
        j=0
        tempdict={}
        for item in row:
            tempdict[key[j]]=item
            j=j+1
        metal_dictionary.append(tempdict)
        ##print(tempdict)
        i=i+1
    metals = copy.deepcopy(metal_dictionary)

def printlist():
    global metals
    for i in metals:
        print(i['colour'])

def print_err():
    print("error: metal with such properties is not known.")
        
def inference(params):
    global metals
    possible_list=[]
    weak_list=[]
    for i in metals:
        colour= params['colour']
        if i['colour'].find(colour) >=0 :
          if params['magnetic'] == i['magnetic']:
              possible_list.append(i)
          else:
              weak_list.append(i)
    for i in possible_list:
          temp_diff=abs(float(i['melting_point'])-float(params['melting_point']))
          density_diff=abs(float(i['density'])-float(params['density']))
          temp_diff= temp_diff/float(i['melting_point'])
          density_diff= density_diff/float(i['density'])
          if temp_diff < 0.25 and density_diff < 0.25:
              print("most probably "+i['name'])


def main():
    knowledge_base()
##    printlist()
    colour = input('Enter colour of metal(shiny/grey/light red/yellow/brown/dull) :')
    density = input ('Enter density of metal :')
    meltin_point = input ('Enter melting point :')
    magnetic = input('Is the metal magnetic (yes/no):')
    list1={'colour':colour,'density':density, 'melting_point':meltin_point, 'magnetic':magnetic}
    inference(list1)

main()
