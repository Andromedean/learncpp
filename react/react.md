# react

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
