module Roll = [%graphql {|
  query rollDice($dice: String!){
    roll(dice: $dice) {
        result { total, details }
    }
  }
|}];

module RollQuery = ReasonApollo.CreateQuery(Roll);

let component = ReasonReact.statelessComponent("Result");

let make = (~dice, ~roll, _children) => {
  ...component,
  render: _ => {
    let rollQuery = Roll.make(~dice, ());
    <RollQuery
      variables=rollQuery##variables
      fetchPolicy="network-only">
      ...{
          ({result, refetch}) =>
            switch (result) {
            | Loading => <div> {ReasonReact.string("Loading")} </div>
            | Error(error) =>
              <div> {ReasonReact.string(error##message)} </div>
            | Data(response) =>
              <div>
                <button
                  className="Button"
                  onClick=(_ => { roll(());  refetch(None) |> ignore })>
                  {ReasonReact.string("Roll")}
                </button>
                <section className="Result">
                  {ReasonReact.string(
                    response##roll
                    -> Belt.Option.map(roll => roll##result)
                    -> Belt.Option.mapWithDefault("", result => string_of_int(result##total))
                  )}
                </section>
              </div>
            }
        }
    </RollQuery>
  },
};
