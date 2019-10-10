# create a new simulator
set ns [new Simulator]

# open trace and NAM trace file in write mode
set tf [open lab.tr w]
$ns trace-all $tf
set nf [open lab.nam w]
$ns namtrace-all $nf

# create 4 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

# create duplex links between nodes
$ns duplex-link $n0 $n2 10Mb 300ms DropTail
$ns duplex-link $n1 $n2 10Mb 300ms DropTail
$ns duplex-link $n2 $n3 1Mb 300ms DropTail

# setup udp connection and set n0 and n1 as source node
set udp0 [new Agent/UDP]
set udp1 [new Agent/UDP]
$ns attach-agent $n0 $udp0
$ns attach-agent $n1 $udp1

# setup cbr(constant bit rate) over udp connection
set cbr0 [new Application/Traffic/CBR]
set cbr1 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
$cbr1 attach-agent $udp1

# set n3 as destination node
set null3 [new Agent/Null]
$ns attach-agent $n3 $null3

# connect source to destination
$ns connect $udp0 $null3
$ns connect $udp1 $null3

# set packet size and interval for both cbr source
$cbr0 set packetSize_ 500Mb
$cbr1 set packetSize_ 500Mb
$cbr0 set interval_ 0.005
$cbr1 set interval_ 0.005

# define a finish procedure
proc finish {} {
	global ns nf tf
	$ns flush-trace
	exec nam lab.nam &
	close $tf 
	close $nf
	
	set count 0
	set tf [open lab.tr r]
	while {[gets $tf line] != -1} {
		if { [string match "*d*" $line] } {
			set count [expr $count + 1]
		}
	}
	puts "No of packets dropped: $count"
	exit 0
}

$ns at 0.01 "$cbr0 start"
$ns at 0.01 "$cbr1 start"
$ns at 5.0 "finish"
$ns run