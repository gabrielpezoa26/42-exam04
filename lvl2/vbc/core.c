typedef struct node {
	enum {
		ADD,
		MULTI,
		VAL 
	}   type;
	int val;
	struct node   *l;
	struct node   *r;
} node;




/* ADDED: declarations of recursive parsing functions */
static node *parse_basic(char **s);
static node *parse_mult(char **s);
static node *parse_add(char **s);


// node n;

// n.type = VAL;
// n.val = **s - '0';
// n.l = NULL;
// n.r = NULL;
/* ADDED: parsing a factor (number or parenthesis) */
static node *parse_basic(char **s)
{
	if (isdigit((unsigned char)**s))
	{
		node n = { .type = VAL, .val = **s - '0', .l = NULL, .r = NULL };
		(*s)++;
		return new_node(n);
	}



	if (accept(s, '('))
	{
		node *e = parse_add(s);
		if (!e)
			return NULL;
		if (!expect(s, ')'))
		{
			destroy_tree(e);
			return NULL;
		}
		return e;
	}
	unexpected(**s);
	return NULL;
}



/* ADDED: parsing a term (multiplications) */
static node *parse_mult(char **s)
{
	node *left = parse_basic(s);
	if (!left)
		return NULL;



	while (accept(s, '*'))
	{
		node *right = parse_basic(s);
		if (!right)
		{
			destroy_tree(left);
			return NULL;
		}



		node n = { .type = MULTI, .l = left, .r = right };
		left = new_node(n);
		if (!left)
			return NULL;
	}
	return left;
}




/* ADDED: parsing an expression (additions) */
/* THIS FUNCTION IS A COPY PASTE OF parse_mult, YOU JUST HAVE TO REPLACE '*' by '+' !!!!!*/
static node *parse_add(char **s)
{
	node *left = parse_mult(s);
	if (!left)
		return NULL;



	while (accept(s, '+'))
	{
		node *right = parse_mult(s);
		if (!right)
		{
			destroy_tree(left);
			return NULL;
		}



		node n = { .type = ADD, .l = left, .r = right };
		left = new_node(n);
		if (!left)
			return NULL;
	}
	return left;
}

/* MODIFIED: parse_expr initializes a local pointer and checks for the end of the string */
node	*parse_expr(char *s)
{
	char *p = s;
	node *ret = parse_add(&p);
	if (!ret)
		return NULL;



	if (*p)
	{
		unexpected(*p);
		destroy_tree(ret);
		return (NULL);
	}
	return ret;
}
