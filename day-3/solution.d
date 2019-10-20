class Node
{
    this(string val = "", Node left = null, Node right = null)
    {
        this.val = val;
        this.left = left;
        this.right = right;
    }

private:
    string val;
    Node left;
    Node right;
}

string serialize(Node node)
{
    return "";
}

Node unserialize(string str)
{
    return new Node();
}

// Final tests
unittest
{
    auto node = new Node("root", new Node("left", new Node("left.left")), new Node("right"));
    assert(unserialize(serialize(node)).left.left.val == "left.left");
}
