let component = ReasonReact.statelessComponent("Input");

let make = (~onChange, ~value, _children) => {
  ...component,

  render: _self => {
    <div>
      <input className="Input" type_="text" placeholder="1d6" value onChange />
    </div>;
  },
};
