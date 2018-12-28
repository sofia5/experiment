setwd("C:/Users/Sofia/Github/experiment/cmake-build-debug/results/Data")
dt <- read.csv("Event_DoubleLinkedList_Worst", sep=",")
dt2<-read.csv("Event_Splaytree_Worst")
rownames(dt)<-dt[,1]
rownames(dt2)<-dt2[,1]
dt<-dt[,-1]
dt2<-dt2[,-1]
#tdt<-t(dt)
#dt2<-t(dt2)
tdt<-t(dt[1:11,])
tdt2<-t(dt2[1:11,])
boxplot(tdt)
boxplot(tdt2, add=TRUE, border="blue")
title(main="Exekveringstid (värsta fallet) för dubbellänkad lista och splaytree", ylab="Tid", xlab="Antal element")
legend("topleft", inset=.05, c("Dubbellänkad lista", "Splaytree"), fill=c("black","blue"), horiz=FALSE)
