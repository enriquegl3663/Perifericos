library(tuneR)
library(seewave)
library(audio)

aaron <- readWave('aaron.wav')
listen(aaron)

enrique <- readWave('enrique.wav')
listen(enrique)

plot( extractWave(aaron, from = 1, to = 167040) )
plot( extractWave(enrique, from = 1, to = 199296) )



str(aaron)
str(enrique)


mezcla <- pastew(enrique, aaron, output="Wave")
listen(mezcla)
writeWave(mezcla, file.path("mezcla.wav"))


plot( extractWave(mezcla, from = 1, to = 366336) )


alreves <- revw(mezcla, output="Wave")
writeWave(alreves, file.path("alreves.wav"))
listen(alreves)


unionECO <- echo(alreves,f=22050,amp=c(1,1,1),delay=c(1,2,3),output="Wave")
listen(unionECO)
writeWave(unionECO, file.path("unionECO.wav"))



