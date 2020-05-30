class GenCode:
    def __init__(self, inpFile):
        self.file = open(inpFile, 'r')
        self.inpFile=inpFile
        self.lineNum = 0
        self.lineMappings = []
        self.addAt = {}
        self.endAt = {}
        self.currentSession = "session0"
        self.operations = {"add", "sub", "mul", "div", "transform"}
        self.dataFrameLines= {}

    def getSession(self):
        self.currentSession = "session" + str(int(self.currentSession[7:]) + 1)
        return self.currentSession
    
    def addAtLine(self, lineNum):
        x = self.currentSession
        print(lineNum)
        self.addAt.update({lineNum: x})
        return x
    
    def endAtLine(self, lineNum, session):
        print(lineNum)
        self.endAt.update({lineNum: session})

    def parse(self):
        l=0

        insess = 0
        current = self.getSession()

        currentSet = {}

        for line in self.file.readlines():
            if ('.' in line  and (line.split('.')[1].startswith("add") or 
                line.split('.')[1].startswith("mul") or 
                line.split('.')[1].startswith("div") or 
                line.split('.')[1].startswith("sub") or
                line.split('.')[1].startswith("transform"))):
                    self.lineNum += 1
                    print("found soemthing, ", insess)
                    if not insess:
                        current = self.addAtLine(self.lineNum - 1) 
                        l = self.lineNum - 1
                    insess = 1

            else:
                    
                    self.lineNum +=1
                    if insess:
                            
                        self.endAtLine(self.lineNum, current)
                        
                        self.lineMappings.append([l, self.lineNum])
                        insess = 0

                        current = self.getSession()
        if insess:
            self.endAtLine(self.lineNum, current)
                        
            self.lineMappings.append([l, self.lineNum])
                        
            
    def removeMappings(self):
        for pair in self.lineMappings:
            if(pair[1] - pair[0] < 4):

                print("removing")
                try:
                    del self.addAt[pair[0]]
                except:
                    pass
                try:
                    del self.endAt[pair[1]]
                except:
                    pass



    def genCode(self):
        outfile = open("out.py", "w")
        i =0
        print(self.addAt, self.endAt)
        for line in open(self.inpFile).readlines():
            if i in self.addAt.keys():
                outfile.write(self.addAt[i] +" = Session()\n")
            if i in self.endAt.keys():
                outfile.write(self.endAt[i] + ".compute()\n" )
            outfile.write(line )
            i+=1

        if i in self.endAt.keys():
            outfile.write( self.endAt[i]+ ".compute()\n")
        outfile.close() 

    def generateGPUSessions(self):
        self.parse()
        self.removeMappings()
        self.genCode()

if __name__ == '__main__':
    example = GenCode("input.py")
    example.generateGPUSessions()