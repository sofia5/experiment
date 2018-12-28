setwd("C:/Users/Sofia/Github/experiment/cmake-build-debug/results/Data")
dt <- read.csv("Event_DoubleLinkedList_Best", sep=",")
dt2<-read.csv("Event_Splaytree_Best")
dt3 <- read.csv("Event_DoubleLinkedList_Worst", sep=",")
dt4 <- read.csv("Event_Splaytree_Worst", sep=",")
rownames(dt)<-dt[,1]
rownames(dt2)<-dt2[,1]
rownames(dt3)<-dt3[,1]
rownames(dt4)<-dt4[,1]
dt<-dt[,-1]
dt2<-dt2[,-1]
dt3<-dt3[,-1]
dt4<-dt4[,-1]
tdt<-t(dt[1:39,])
tdt2<-t(dt2)
tdt3<-t(dt3)
tdt4<-t(dt4)
boxplot(tdt, border="pink")
boxplot(tdt2, add=TRUE, border="light blue")
boxplot(tdt3, add=TRUE, border="red")
boxplot(tdt4, add=TRUE, border="dark blue")

title(main="Exekveringstid (bästa/värsta fallet) för dubbellänkad lista och splaytree", ylab="Tid", xlab="Antal element")
legend("topleft", inset=.05, c("Dubbellänkad lista", "Splaytree"), fill=c("red","blue"), horiz=FALSE)

