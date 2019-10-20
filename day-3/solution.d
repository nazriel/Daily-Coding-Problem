import std.format: format;
import std.array: replace;

struct Stack
{
    void push(Node n)
    {
        this.nodes ~= n;
    }

    Node pop()
    {
        auto n = this.nodes[$-1];
        this.nodes = this.nodes[0..$-1];
        return n;
    }

    @property size_t length()
    {
        return nodes.length;
    }

    Node[] nodes;
}

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
    Stack stack;
    Node rootNode = null;
    auto currentNode = rootNode;

    void handleNewNode(ref string s)
    {
        stack.push(currentNode);
        currentNode = new Node();
        s = s[2..$];

        if (!rootNode)
        {
            rootNode = currentNode;
        }
    }

    void handleValue(ref string s)
    {
        auto len = 0;
        if (s[2] != '"')
            throw new Exception(`Couldn't match opening " when parsing value: ` ~ s[2]);

        s = s[3..$];
        while (true)
        {
            if (len >= s.length)
                throw new Exception(`Couldn't match closing " when parsing value`);
            if (s[len] == '"' && s[len - 1] != '\\')
                break;
            len++;
        }
        currentNode.val = s[0 .. len].replace(`\"`, `"`);
        s = s[len + 1 .. $];
        if (s[0..$] == ", ")
            s = s[2..$];
    }

    void handleLeftNode(ref string s)
    {
        s = s[4..$];
        currentNode.left = new Node();
        stack.push(currentNode);
        currentNode = currentNode.left;
    }

    void handleRightNode(ref string s)
    {
        s = s[4..$];
        currentNode.right = new Node();
        stack.push(currentNode);
        currentNode = currentNode.right;
    }

    auto slice = str[];
    while (slice.length > 2)
    {
        switch (slice[0..2]) {
        case "n(":
            handleNewNode(slice);
            break;
        case "v=":
            handleValue(slice);
            break;
        case "l=":
            handleLeftNode(slice);
            break;
        case "r=":
            handleRightNode(slice);
            break;
        case ", ":
            slice = slice[2..$];
            break;
        case "),":
            currentNode = stack.pop();
            if (!currentNode)
                throw new Exception("Malformed string");

            slice = slice[3..$];
            break;
        case "))":
            if (stack.length < 2)
                throw new Exception("Malformed string");

            stack.pop();
            currentNode = stack.pop();
            slice = slice[2..$];
            break;
        default:
            throw new Exception("Malformed string");
        }
    }

    return rootNode;
}

// positive cases
unittest
{
    auto str = `n(v="root", l=n(v="root.left", l=n(v="root.left.left")), r=n(v="root.right"))`;
    auto n = unserialize(str);
    assert(n.val == `root`);
    assert(n.left.val == `root.left`);
    assert(n.left.left.val == `root.left.left`);
    assert(n.right.val == `root.right`);

    str = `n(l=n(l=n(l=n(l=n(l=n(l=n(v="deep")))))))`;
    n = unserialize(str);
    assert(n.left.left.left.left.left.left.val == `deep`);
}

// weird values
unittest
{
    auto str = `n(v="l=n(r=n(v=\"abcd\"))")`;
    auto n = unserialize(str);
    assert(n.val == `l=n(r=n(v="abcd"))`, n.val);

    str = `n(v="abcd\\"e")`;
    n = unserialize(str);
    assert(n.val == `abcd\"e`, n.val);
}

// parsing exceptions
unittest
{
    import std.exception: collectException;
    auto str = `n(v="root l=n(v="root.left", l=n(v="root.left.left")), r=n(v="root.right"))`;
    auto exception = collectException(unserialize(str));
    assert(exception);
    assert(exception.msg == "Malformed string", exception.msg);

    str = `n(v="root )`;
    exception = collectException(unserialize(str));
    assert(exception);
    assert(exception.msg == `Couldn't match closing " when parsing value`, exception.msg);
}

// Final tests
unittest
{
    auto node = new Node("root", new Node("left", new Node("left.left")), new Node("right"));
    assert(unserialize(serialize(node)).left.left.val == "left.left");
}
