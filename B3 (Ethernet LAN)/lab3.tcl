# Declare a new Simulator
set ns [new Simulator]

# Open nam and trace file in write mode
set tf [open out.tr w]
set nf [open out.nam w]
$ns trace-all $tf
$ns namtrace-all $nf

# Create nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]

# vary this for different output
set erate 0.2
set psize 500Mb
set ptime 0.001

# set label and color (OPTIONAL)
$n1 label "udp/source"
$n5 label "udp/null"
$n0 color "blue"
$n1 color "blue"
$n2 color "blue"
$n3 color "blue"
$n4 color "red"
$n5 color "red"
$n6 color "red"

# Create two lans
$ns make-lan "$n0 $n1 $n2 $n3" 10Mb 10ms LL Queue/DropTail Mac/802_3
$ns make-lan "$n4 $n5 $n6" 10Mb 10ms LL Queue/DropTail Mac/802_3

# Setup Links
$ns duplex-link $n3 $n6 10Mb 10ms DropTail

# Declare the protocol and source and destination node
set udp1 [new Agent/UDP]
set null5 [new Agent/Null]
$ns attach-agent $n1 $udp1
$ns attach-agent $n5 $null5

# Declare the application layer protocol
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1

# Create error model
set err [new ErrorModel]
$ns lossmodel $err $n3 $n6
$err set rate_ $erate

# Connect the source and destination
$ns connect $udp1 $null5

# Vary the packetSize and interval for different output
$cbr1 set packetSize_ $psize
$cbr1 set interval_ $ptime

# Define procedure
proc finish { } {
	global ns nf tf erate psize ptime
	$ns flush-trace
	exec nam out.nam &
	close $nf
	close $tf

	set count 0
	set tr [open out.tr r]
	while {[gets $tr line] != -1} {
		# 8 denotes LAN at destination side and 5 denotes destination node
		if {[string match "* 8 5 *" $line]} {
			set count [expr $count+1]
		}
	}
	
	set thr [expr $count/5]
	puts "Error rate : $erate"
	puts "Data rate  : $psize/$ptime sec"
	puts "Throughput : $thr"
	exit 0
}

$ns at 0.1 "$cbr1 start"
$ns at 5.0 "finish"
$ns run

######################### output-1 #####################
# nplaba1@linux-HP-Pro-3090-MT:~/akshat$ ns lab3.tcl
# Error rate : 0.2
# Data rate  : 500Mb/0.001 sec
# Throughput : 781

######################### output-2 #####################
# nplaba1@linux-HP-Pro-3090-MT:~/akshat$ ns lab3.tcl
# Error rate : 0.3
# Data rate  : 1000Mb/0.001 sec
# Throughput : 681

############################ NAM output ################
#
#            [udp1]               duplex-link
#	   [n0]	  [n1]	 [n2]	[n3]-------------
#       |      |      |      |              |
#       |      |      |      |              |
#   -------------------------------lan7		|
#											|
#   -------------------------------lan8		|
#        |       |        |                 |
#        |       |        |                 |
#       [n4]    [n5]     [n6]----------------	
#              [null5]
#
#########################################################
