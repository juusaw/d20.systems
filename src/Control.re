type state = {
  inputValue: string,
  submittedValue: string,
};

type action =
  | Write(string)
  | Roll;

let component = ReasonReact.reducerComponent("Control");

let make = _children => {
  ...component,

  initialState: () => {inputValue: "", submittedValue: ""},

  reducer: (action: action, state: state) =>
    switch (action) {
    | Write(newDice) => ReasonReact.Update({...state, inputValue: newDice})
    | Roll => ReasonReact.Update({...state, submittedValue: state.inputValue})
    },

  render: self => {
    <div>
      <input
        className="Input"
        type_="text"
        placeholder="Example: 1d6"
        value={self.state.inputValue}
        onChange={e => self.send(Write(ReactEvent.Form.target(e)##value))}
        onKeyDown={e =>
          switch (ReactEvent.Keyboard.key(e)) {
          | "Enter" => self.send(Roll)
          | _ => ignore()
          }
        }
      />
      <Result dice={self.state.submittedValue} roll={_ => self.send(Roll)} />
      <Statistics dice={self.state.submittedValue} />
    </div>;
  },
};
