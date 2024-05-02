# react
[react quick start](https://react.dev/learn)

## component
- a piece of UI with its own logic and appearance
  - eg: button or whole page
- js functions that return markup
  - markup is written in JSX
- component names always start with a capital
```js
function MyButton() {
  return (
    <button>I'm a button</button>
  );
}
```
- may then nest into other components
```js
export default function MyApp() {
  return (
    <div>
      <h1>Welcome to my app</h1>
      <MyButton />
    </div>
  );
}
```

## style
- css class specified with ```className```
```js <img className="avatar" /> ```
- css rules written in different file
```css
/* In your CSS */
.avatar {
  border-radius: 50%;
}
```
- to link: the simplest case, you’ll add a ```<link>``` tag to your HTML

## displaying data
- {} let you 'escape' back to js
```js
return (
  <h1>
    {user.name}
  </h1>
);
```
- can use the style attribute when your styles depend on JavaScript variables.
```js
<img
  className="avatar"
  src={user.imageUrl}
  alt={'Photo of ' + user.name}
  style={{
    width: user.imageSize,
    height: user.imageSize
  }}
/>
```
- style={{}} is not a special syntax, but a regular {} object inside the style={ } JSX curly braces
- can use the style attribute when your styles depend on JavaScript variables

## conditional rendering
- just use js
```js
let content;
if (isLoggedIn) {
  content = <AdminPanel />;
} else {
  content = <LoginForm />;
}
return (
  <div>
    {content}
  </div>
);
```
- may use ternary in jsx
```js
<div>
  {isLoggedIn ? (
    <AdminPanel />
  ) : (
    <LoginForm />
  )}
</div>
```
- or if no else is needed, use &&
```js
<div>
  {isLoggedIn && <AdminPanel />}
</div>
```
- these all work for specifying attributes

## rendering lists
- use js map() or for loop to render list
```js
const products = [
  { title: 'Cabbage', isFruit: false, id: 1 },
  { title: 'Garlic', isFruit: false, id: 2 },
  { title: 'Apple', isFruit: true, id: 3 },
];

export default function ShoppingList() {
  const listItems = products.map(product =>
    <li
      key={product.id}
      style={{
        color: product.isFruit ? 'magenta' : 'darkgreen'
      }}
    >
      {product.title}
    </li>
  );

  return (
    <ul>{listItems}</ul>
  );
}
```

## responding to events
- declare event handler functions in component
```js
function MyButton() {
  function handleClick() {
    alert('You clicked me!');
  }

  return (
    <button onClick={handleClick}>
      Click me
    </button>
  );
}
```

## state
- updating a state rerenders the component
```js
import { useState } from 'react';

export default function MyApp() {
  return (
    <div>
      <h1>Counters that update separately</h1>
      <MyButton />
      <MyButton />
    </div>
  );
}

function MyButton() {
  const [count, setCount] = useState(0);

  function handleClick() {
    setCount(count + 1);
  }

  return (
    <button onClick={handleClick}>
      Clicked {count} times
    </button>
  );
}
```

## hooks
- lets you use different react features from components
- functions starting with 'use' are hooks like useState in the state example
### effect hooks
- used to connect and sync with external systems
```js
function ChatRoom({ roomId }) {
  useEffect(() => {
    const connection = createConnection(roomId);
    connection.connect();
    return () => connection.disconnect();
  }, [roomId]);
  // ...
```

### custom hooks
- combine hooks in custom hooks
  - let you share stateful logic not the state itself
- code inside custom hooks runs on every render

## sharing data between components
- 'lift state up'
- declare in a higher component and pass down to each component
```js
import { useState } from 'react';

export default function MyApp() {
  // declared in MyApp()
  const [count, setCount] = useState(0);

  function handleClick() {
    setCount(count + 1);
  }

  return (
    <div>
      <h1>Counters that update together</h1>
      // passed to the lower components
      <MyButton count={count} onClick={handleClick} />
      <MyButton count={count} onClick={handleClick} />
    </div>
  );
}

function MyButton({ count, onClick }) {
  return (
    <button onClick={onClick}>
      Clicked {count} times
    </button>
  );
}
```
