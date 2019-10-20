import std.format: format;
import std.array: replace;

class Node
{
    this(string val = "", Node left = null, Node right = null)
    {
        this.val = val;
        this.left = left;
        this.right = right;
    }

    override string toString()
    {
        return serialize(this);
    }

private:
    string val;
    Node left;
    Node right;
}

string serialize(Node node)
{
    string r = "";
    r ~= `n(v="%s"`.format(node.val.replace(`"`, `\"`));

    if (node.left || node.right)
    {
        r ~= ", ";
    }

    if (node.left)
    {
        r ~= "l=" ~ serialize(node.left);
    }

    if (node.right)
    {
        if (node.left)
            r ~= ", ";

        r ~= "r=" ~ serialize(node.right);
    }
    r ~= ")";
    return r;
}

unittest
{
    auto node = new Node("root", new Node("root.left", new Node("root.left.left")), new Node("root.right"));
    auto s = serialize(node);
    assert(s == `n(v="root", l=n(v="root.left", l=n(v="root.left.left")), r=n(v="root.right"))`, s);

    node = new Node("");
    s = serialize(node);
    assert(s == `n(v="")`, s);

    node = new Node(`"`);
    s = serialize(node);
    assert(s == `n(v="\"")`, s);

    node = new Node(``, new Node(""), new Node(""));
    s = serialize(node);
    assert(s == `n(v="", l=n(v=""), r=n(v=""))`, s);
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
