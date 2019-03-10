module RollStats = [%graphql
  {|
  query rollDice($dice: String!){
    roll(dice: $dice) {
      statistics { distribution, min, max, average }
    }
  }
|}
];

module RollStatsQuery = ReasonApollo.CreateQuery(RollStats);

let component = ReasonReact.statelessComponent("Statistics");

type dataPoint = Victory.victoryData;

let toDataPoints: Js.Array.t(int) => array(Victory.victoryData) = [%bs.raw
  {|
  function (data) {
    return Array.from(data.reduce((m, x) => m.set(x, (m.get(x) || 0) + 1) , new Map())).map(([x, y]) => ({x, y}))
  }
|}
];

let make = (~dice, _children) => {
  ...component,
  render: _self => {
    let rollStatsQuery = RollStats.make(~dice, ());
    <RollStatsQuery
      variables=rollStatsQuery##variables skip={String.length(dice) == 0}>
      ...{({result}) =>
        switch (result) {
        | Loading => <div> {ReasonReact.string("Loading")} </div>
        | Error(error) => <div> {ReasonReact.string(error##message)} </div>
        | Data(response) =>
          let distribution =
            response##roll
            ->Belt.Option.flatMap(roll => roll##statistics##distribution);
          let data =
            distribution->Belt.Option.mapWithDefault(
              [||]: array(dataPoint), distr =>
              toDataPoints(distr)
            );
          switch (Array.length(data)) {
          | 0 => ReasonReact.null
          | _ =>
            Victory.(
              <VictoryChart domainPadding=20 theme=VictoryTheme.material>
                <VictoryAxis />
                <VictoryStack colorScale="grayscale">
                  <VictoryBar data />
                </VictoryStack>
              </VictoryChart>
            )
          };
        }
      }
    </RollStatsQuery>;
  },
};
