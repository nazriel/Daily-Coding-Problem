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
