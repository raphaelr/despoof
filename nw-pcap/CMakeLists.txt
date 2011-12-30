file(GLOB Sources *.cpp *.h)
add_library(nw-pcap MODULE ${Sources})
target_link_libraries(nw-pcap common-nw wpcap)
