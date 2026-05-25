echo "set(SOURCES"
    find cpp -name "*.cpp" | sort | awk '{print "    "$0}'
echo ")"
