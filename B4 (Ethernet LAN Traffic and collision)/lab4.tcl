# Author : Akshat Agarwal

# 4. Simulate an Ethernet LAN using n nodes and set multiple traffic nodes and determine the collision across different nodes.


# Declare a new Simulator
set ns [new Simulator]

# Open the trace and nam file in write mode
set tf [open out.tr w]
set nf [open out.nam w]
$ns trace-all $tf
$ns namtrace-all $nf

# Decide the topology: [tcp(0->2)], [udp(2->1)], [tcp(1->3)]
#
#      [tcp0]   [tcp1][null1]
#       [n0]        [n1]
#        |           |
#        |           |
#   ------------------------------ lan4
#            |             |
#            |             |
#           [n3]          [n2]
#         [sink3]     [udp2][sink2]

# Create 4 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

# Create lan and setup the link
$ns make-lan -trace on "$n0 $n1 $n2 $n3" 100Mb 10ms LL Queue/DropTail Mac/802_3

# Declare the required transport layer Protocols
set tcp0 [new Agent/TCP]
set tcp1 [new Agent/TCP]
set udp2 [new Agent/UDP]
set null1 [new Agent/Null]
set sink2 [new Agent/TCPSink]
set sink3 [new Agent/TCPSink]

# Attach these Protocols to their respective nodes
$ns attach-agent $n0 $tcp0
$ns attach-agent $n1 $tcp1
$ns attach-agent $n2 $udp2
$ns attach-agent $n1 $null1
$ns attach-agent $n2 $sink2
$ns attach-agent $n3 $sink3

# Declare Application layer protocols and attach them with their transport layer protocols
set ftp0 [new Application/FTP]
set ftp1 [new Application/FTP]
set cbr2 [new Application/Traffic/CBR]
$ftp0 attach-agent $tcp0
$ftp1 attach-agent $tcp1
$cbr2 attach-agent $udp2

# connect source to destination
$ns connect $tcp0 $sink2
$ns connect $udp2 $null1
$ns connect $tcp1 $sink3

# set the interval 
$ftp0 set interval_ 0.001
$ftp1 set interval_ 0.001
$cbr2 set interval_ 0.01

# define finish procedure
proc finish {} {
	global ns nf tf
	$ns flush-trace
	exec nam out.nam &
	close $tf
	close $nf
	
	set count 0
	set tr [open out.tr r]
	while {[gets $tr line] !=-1 } {
		if { [string match "c*" $line] } {
			set count [expr $count + 1]
		}
	}
	puts "No of packets collided: $count"
	exit 0
}

# schedule the events
$ns at 0.1 "$cbr2 start"
$ns at 0.1 "$ftp0 start"
$ns at 0.1 "$ftp1 start"
$ns at 5.0 "finish"
$ns run

############ output ############

# No of packets collided: 242

################################