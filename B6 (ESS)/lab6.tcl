# Author : Akshat Agarwal

# 6. A Simple ESS with transmitting nodes in Wireless LAN
# 7. A simple ad-hoc network with transmitting nodes


# Declare new Simulator
set ns [new Simulator]

# Open the trace file in write mode
set tf [open out.tr w]
$ns trace-all $tf

# Set name-trace for wireless network
set nf [open out.nam w]
$ns namtrace-all-wireless $nf 500 500

# Set new topography
set topo [new Topography]
$topo load_flatgrid 500 500

# Configure for a wireless node.
$ns node-config -adhocRouting DSDV \
-llType LL \
-macType Mac/802_11 \
-ifqType Queue/DropTail \
-ifqLen 50 \
-phyType Phy/WirelessPhy \
-channelType Channel/WirelessChannel \
-propType Propagation/TwoRayGround \
-antType Antenna/OmniAntenna \
-topoInstance $topo \
-agentTrace ON \
-routerTrace ON \
-macTrace OFF 

# Create a god object
create-god 3

################### Decide the topology ###############
#   500
#   |
#   |
#   |							
#   400                         [sink2]
#   |                            [n2]	
#   |                           .'
#   |                         .'
#   |                       .'
#   |                     .'
#   |                   .'
#   |                 .'
#   100            [n1]
#   |          .' [sink1]	
#   |        .'   [tcp1]
#   10   [n0]     [ftp1]
#   |  [tcp0]
#   |  [ftp0]
#   |
#   |____10______100_______________400_________500

# Create nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

# Locate the nodes on load_flatgrid
$n0 set X_ 10
$n0 set Y_ 10
$n0 set Z_ 0

$n1 set X_ 100
$n1 set Y_ 100
$n1 set Z_ 0

$n2 set X_ 400
$n2 set Y_ 400
$n2 set Z_ 0

# initial state
$ns at 0.0 "$n0 setdest 10 10 15"
$ns at 0.0 "$n1 setdest 100 100 15"
$ns at 0.0 "$n2 setdest 400 400 15"

# move n1 near to node n2 at 50s and come back near to node n0 at 100s
$ns at 50 "$n1 setdest 300 300 15"
$ns at 100 "$n1 setdest 100 100 15"

# Declare and attach transport layer protocol
set tcp0 [new Agent/TCP]
set tcp1 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
$ns attach-agent $n1 $tcp1

set sink1 [new Agent/TCPSink]
set sink2 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1
$ns attach-agent $n2 $sink2

# Declare and attach appliction layer protocol
set ftp0 [new Application/FTP]
set ftp1 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ftp1 attach-agent $tcp1

# connect source to destination
$ns connect $tcp0 $sink1
$ns connect $tcp1 $sink2


proc finish { } {
    global ns nf tf
    $ns flush-trace
    exec nam out.nam &
    close $tf

    set ctr1 0
    set ctr2 0
    set tf [open out.tr r]
    
    while {[gets $tf line] != -1} {
        # r->received, _1_ -> destination node
        if {[string match "r*_1_*AGT*" $line]} {
            set ctr1 [expr $ctr1 + 1]
        }
        if {[string match "r*_2_*AGT*" $line]} {
            set ctr2 [expr $ctr2 + 1]
        }
    }
    puts "\nThroughput from n0 to n1: $ctr1"
    puts "Throughput from n1 to n2: $ctr2"
    exit 0
}

# schedule events

# start ftp traffic
$ns at 1 "$ftp0 start"
$ns at 1 "$ftp1 start"
$ns at 150 "finish"
$ns run

######################## output ###########################

# num_nodes is set 3
# INITIALIZE THE LIST xListHead
# channel.cc:sendUp - Calc highestAntennaZ_ and distCST_
# highestAntennaZ_ = 1.5,  distCST_ = 550.0
# SORTING LISTS ...DONE!
#
# Throughput from n0 to n1: 8438
# Throughput from n1 to n2: 3000

############################################################
