let inMemoryCache = ApolloInMemoryCache.createInMemoryCache(());

let httpLink = ApolloLinks.createHttpLink(
  ~uri="https://d20ql.now.sh/graphql", ());

let instance =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());
