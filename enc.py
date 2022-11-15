#!/bin/python3

import hashlib as hasher
import sys

def sha256(password):
    return hasher.sha256(password.encode('utf-8')).hexdigest()
  
def readfile(filename):
    
    with open(filename, 'r',encoding = "ISO-8859-1") as f:
      lines=f.readlines()
      for line in lines:
          line=sha256(line)
          with open("hashes.txt","a") as file:
          
           file.write(line)
    f.close()
    file.close()  
    return 0;         
           
def compare():
  password="73c4e9dcdb9f69899386d2f7b9c17965b02632607b0faf7f727d30ef99159888"
  with open("/Users/jared/Desktop/hashes.txt","r",encoding = "ISO-8859-1" ) as file:
    lines=file.readlines()
    for line in lines:
      if line==password:
        print("password is: "+line)
        return 0;
      else:
        print("password not found")  
        
        
readfile("/Users/jared/Desktop/rockyou.txt")    
compare()  
  