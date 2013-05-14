#
# plots.R -- process graphs for the Birch and Swinnerton-Dyer conjecture
#
# (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
#
data <- read.csv("data.csv")

p = data[,1]
maxp = max(p)
Np = data[,2]

dotsize = 0.5

pdf("bsd.pdf", width = 11, height = 8)

# first graph: raw data
plot(p, Np, pch = 16, col = "red", cex = dotsize,
	main = "Np for y^2 = x^3 - 5x")
lines(c(0,maxp), c(0, maxp), col="blue", lwd = 3)

# second graph: relative size of Np, i.e. Np/p versus p

quotients = Np / p

plot(p, quotients, pch = 16, col = "red", cex = dotsize,
	main = "Np/p for y^2 = x^3 - 5x",
	xlab = "p", ylab = "Np/p")
lines(c(0,maxp), c(1,1), col = "blue", lwd = 3)

# third graph: logarithmic relative size, log(Np/p) versus p
logquotients = log10(quotients)
plot(p, logquotients, pch = 16, col = "red", cex = dotsize,
	main = "log(Np/p) for y^2 = x^3 - 5x",
	xlab = "p", ylab = "Np/p", ylim = c(-0.1,0.1))
lines(c(0,maxp), c(0,0), col = "blue", lwd = 3)

# fourth graph: are values predominantly positive or negative? Take sums
sums = cumsum(logquotients)
plot(p, sums, pch = 16, col = "red", cex = dotsize,
	main = "Sum of log(Np/p) for y^2 = x^3 - 5x",
	xlab = "x", ylab = "Sum of log(Np/p) for p < x")

# fourth graph: use log scale on x-axis
x = log10(p)
plot(x, sums, pch = 16, col = "red", cex = dotsize,
	main = "Sum of log(Np/p) for y^2 = x^3 - 5x, log scale",
	xlab = "log(x)", ylab = "Sum of Np/p for p < x")

# fifth graph: use log log scale on x-axis
x = log10(log10(p))
plot(x, sums, pch = 16, col = "red", cex = dotsize,
	main = "Sum of log(Np/p) for y^2 = x^3 - 5x, log-log scale",
	xlab = "log(log(x))", ylab = "Log of Product of Np/p with p < x")

# add line of slope 1 for the Birch and Swinnerton-Dyer conjecture
r = 1
C = 0.88
endpoints = c(log10(log10(2)), log10(log10(maxp)))
lines(endpoints, r * endpoints + C, col = "blue", lwd = 3)

