
/* ADDED: declarations of recursive parsing functions */
static node *parse_expr_r(char **s);
static node *parse_term   (char **s);
static node *parse_factor (char **s);

/* ADDED: parsing a factor (number or parenthesis) */
static node *parse_factor(char **s)
{
	if (isdigit((unsigned char)**s))
	{
		node n = { .type = VAL, .val = **s - '0', .l = NULL, .r = NULL };
		(*s)++;
		return new_node(n);
	}
	if (accept(s, '('))
	{
		node *e = parse_expr_r(s);
		if (!e)
			return NULL;
		if (!expect(s, ')')) {         // MOD: closing parenthesis check
			destroy_tree(e);
			return NULL;
		}
		return e;
	}
	unexpected(**s);
	return NULL;
}

/* ADDED: parsing a term (multiplications) */
static node *parse_term(char **s)
{
	node *left = parse_factor(s);
	if (!left)
		return NULL;
	while (accept(s, '*'))
	{
		node *right = parse_factor(s);
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
/* THIS FUNCTION IS A COPY PASTE OF PARSE_TERM, YOU JUST HAVE TO REPLACE '*' by '+' !!!!!*/
static node *parse_expr_r(char **s)
{
	node *left = parse_term(s);
	if (!left)
		return NULL;
	while (accept(s, '+'))
	{
		node *right = parse_term(s);
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
node *parse_expr(char *s)
{
	char *p = s;
	node *ret = parse_expr_r(&p);
	if (!ret)
		return NULL;
	if (*p)
	{
		unexpected(*p);
		destroy_tree(ret);
		return NULL;
	}
	return ret;
}