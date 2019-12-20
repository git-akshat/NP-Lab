# Author : Akshat Agarwal

# 5. Simulate the transmission of ping messages over a network topology consisting of 6 nodes and find the number of packets dropped due to congestion.


# Declare new Simulator
set ns [new Simulator]

# Open trace and nam file in write mode
set tf [open out.tr w]
set nf [open out.nam w]
$ns trace-all $tf
$ns namtrace-all $nf

# Decide the topology
#
#   [s0][ping]      [ping]      [ping]
#      [n0]          [n1]        [n3]
#         '.          |          .'	
#           '.        |        .'
#             '.      |      .'
#               '.    |    .'
#                 '.  |  .'
#                    [n2]
#                  .' | '.
#                .'   |   '.
#              .'     |     '.
#            .'       |       '.
#          .'         |         '.
#        .'           |           '.
#      [n4]          [n5]         [n6]
#    [ping][d0]   [s1][ping]   [ping][d1]

# Create the nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]

# set up links
$ns duplex-link $n0 $n2 100Mb 300ms DropTail
$ns duplex-link $n5 $n2 100Mb 300ms DropTail
$ns duplex-link $n1 $n2 100Mb 300ms DropTail
$ns duplex-link $n3 $n2 100Mb 300ms DropTail
$ns duplex-link $n2 $n4 100Mb 300ms DropTail
$ns duplex-link $n2 $n6 100Mb 300ms DropTail

# Declare the agents/protocols
set ping0 [new Agent/Ping]
set ping4 [new Agent/Ping]
set ping5 [new Agent/Ping]
set ping6 [new Agent/Ping]

# Attach the ping with the respective nodes
$ns attach-agent $n0 $ping0
$ns attach-agent $n4 $ping4
$ns attach-agent $n5 $ping5
$ns attach-agent $n6 $ping6

# Connect the ping from source to destination
$ns connect $ping0 $ping4
$ns connect $ping5 $ping6

# Write proc for ping agent
Agent/Ping instproc recv {from rtt} {
	$self instvar node_
	puts "The node [$node_ id] recieved $from with round trip time $rtt"
}

# Write the proc function
proc finish { } {
	global ns nf tf
	$ns flush-trace
	exec nam out.nam &
	close $nf
	close $tf

	set count 0
	set tr [open out.tr r]
	while {[gets $tr line]!=-1} {
		if {[string match "d*" $line]} {
			set count [expr $count + 1]
		}
	}
	puts "No. of packet dropped : $count"
	exit 0
}

# shut down link between n2 and n6 for 1 sec(2 - 1 = 1) to show packet dropping
$ns rtmodel-at 1 down $n2 $n6
$ns rtmodel-at 2 up $n2 $n6

# schedule events
for {set i 0.1} {$i<2} {set i [expr $i+0.1]} {
    $ns at $i "$ping0 send"
    $ns at $i "$ping5 send"
}

$ns at 5.0 "finish"
$ns run

####################### output #####################
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 3 recieved 4 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 3 recieved 4 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 3 recieved 4 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 3 recieved 4 with round trip time 1201.0
# No. of packet dropped : 5
####################################################