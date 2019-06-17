let currentUser;
let productUser;
const sleep = (milliseconds) => {
  return new Promise(resolve => setTimeout(resolve, milliseconds))
}
function addUser(user_name) {
  const uname = document.getElementById(user_name);
  console.log("addUser called: "+uname.value);
  collection.insertOne(
      {
        user : uname.value,
        wallet : 0,
        rating : 0.0,
        sold : 0,
        store : [],
        order_history : []
      })
  .then(() => {console.log("success")})
  .catch(err => {console.error(err)});
}

function deleteUser(user_name) {
  const uname = document.getElementById(user_name);
  console.log("deleteUser called: "+uname.value);
  collection.deleteOne({user : uname.value})
    .then(() => {console.log("success")})
    .catch(err => {console.error(err)});
}

function getHistory() {
  collection.findOne({_id:currentUser}).then(r=>{
      const hist = r.order_history.map(h=>{
          "<ul><li>"+h.name+"</li><li>"+h.qtt+
          "</li><li>"+h.rate+"/li></ul>";
          });
      return "<ol><li>"+hist.join('</li><li>')+
        "</li></ol>";
      })
  .catch(e=>{console.error(e)});

}

function loginUser(user_name) {
  const uname = document.getElementById(user_name);
  console.log("loginUser called: "+uname.value);
  collection.findOne({user:uname.value}).then(rslt => {
      if (!rslt)
        alert("No such user!");
      else {
        currentUser = rslt._id;
        document.getElementById("user_header_name")
          .innerHTML="User Name: "+rslt.user;
        document.getElementById("user_header_wallet")
          .innerHTML="Wallet: "+rslt.wallet;
        document.getElementById("user_header_rating").
          innerHTML="Rating: "+rslt.rating.toFixed(2);
        const list = document.getElementById("user_store_list");
        const plist = rslt.store.map(p => "<li>"+p.pname+"</li>").join('');
        list.innerHTML = "<ul>" + plist + "</ul>";
        const hist_div = document.getElementById('history');
        if (rslt.order_history.length > 0) {
          const mapr = rslt.order_history.map(h=>{
              const s = "<ul><li>Name: "+h.name+"</li><li>Quantity: "+h.qtt+
            "</li><li>Given rating: "+h.rate+"</li></ul>";
            console.log(s);
            return s;
            }).join("</li><li>");
          const str = "<ol><li>"+mapr+"</li></ol>";
          hist_div.innerHTML = str;
        } else {
          hist_div.innerHTML = "No record found";
        }
      }})
    .then(() => {console.log("login success")})
    .catch(e => {console.error(e)});
}

function refreshUsers() {
  console.log("refreshUsers called");
  collection.find({}).toArray().then(rslt => {
      const users = rslt.map(u => "<li>"+u.user+"</li>").join('');
      const content = "<ol>"+users+"</ol>";
      document.getElementById("user_list").innerHTML = content;
      })
  .then(() => {console.log("refresh success")})
  .catch(e => {console.error(e)});
}

function updateWallet(bool) {
  const uname = document.getElementById("user_header_name").innerHTML;
  const wallet = document.getElementById("user_header_wallet");
  const change = document.getElementById("change_amount").value;
  const str = uname.substring(uname.indexOf(':')+2);
  const w_amount = wallet.innerHTML
    .substring(wallet.innerHTML.indexOf(':')+2);
  console.log("Selected User: "+str);
  let new_amount;
  if (bool)
    new_amount = +w_amount + +change;
  else
    new_amount = +w_amount - +change;
  console.log("new wallet: " + new_amount);
  if(str) {
    collection.updateOne({user:str}, {$set: {wallet: new_amount}})
      .then(() => {
          wallet.innerHTML="Wallet: "+new_amount;
          console.log("success")})
      .catch(err => {console.error(err)});

  } else {alert("No logged in user")}
}

function updateWalletHelper(change) {
  collection.updateOne({_id:currentUser}, {$inc : {wallet:change}})
    .then(()=>{console.log('update success')})
    .catch(e=>{console.error(e)});
}

function updateWalletHelperWithName(name, change) {
  collection.updateOne({user:name}, {$inc : {wallet:change}})
    .then(()=>{console.log('update success')})
    .catch(e=>{console.error(e)});
}

function addProduct() {
  const pname = document.getElementById("product_name").value;
  const purl = document.getElementById("product_url").value;
  const pprice = document.getElementById("product_price").value;
  const pqtt = document.getElementById("product_qtt").value;
  collection.updateOne({_id:currentUser}, { $push : {store : { 
      pname : pname,
      purl : purl,
      pprice : pprice,
      pqtt : +pqtt
    }}})
  .then(() => {console.log("success")})
  .catch(e => {console.error(e)});
}

function getProduct() {
  const uname = document.getElementById('user_name_q').value;
  const pname = document.getElementById('product_name_q').value;
  collection.findOne({user:uname})
    .then(r => {
        console.log("getProd success");
        productUser = JSON.parse(JSON.stringify(r));
        const prod = r.store.find(l => l.pname == pname);
        document.getElementById('prod_info_name').innerHTML = 
          "Product Name: " + prod.pname;
        document.getElementById('prod_info_price').innerHTML = 
          "Price: " + prod.pprice;
        document.getElementById('prod_info_qtt').innerHTML = 
          "Quantity: " + prod.pqtt;
        document.getElementById('prod_info_seller').innerHTML =
          "Seller: " + r.user;
        document.getElementById('prod_info_rating').innerHTML =
          "Seller Rating: " + r.rating.toFixed(2);
        document.getElementById('prod_info_img').innerHTML =
          "Photo: ";
        document.getElementById('product_img').src = prod.purl;
    })
    .catch(e=>{console.error(e)});
}

function dropProduct() {
  const pname = document.getElementById("delete_prod").value;
  collection.updateOne({_id:currentUser}, {$pull:{store:{pname:pname}}})
    .then(()=>{console.log('success')})
    .catch(e=>{console.error(e)});
}

function decreaseQuantity(name, prod, qtt) {
  return collection.updateOne({user:name, "store.pname":prod},
      {$inc:{"store.$.pqtt":-qtt}})
    .then(()=>{console.log('decrease success')})
    .catch(e=>{console.error('decr error')});
}

function updateRatingOfUser(name, rate) {
  return collection.updateOne({user:name}, {$inc : {
      sold : 1, 
      rating:(rate-productUser['rating'])/(+productUser['sold']+1)}})
    .then(()=>{console.log('rate update success')})
    .catch(e=>{console.error(e)});
}

function updateOrderHistory(pname, qtt, rate) {
  collection.updateOne({_id:currentUser}, {$push : {order_history :
      {
        name:pname,
        qtt:qtt,
        rate:rate
      }}})
  .then(()=>{console.log('history success')})
  .catch(e=>{console.error(e)});
}

function buy() {
  const uname = document.getElementById('user_name_q').value;
  const pname = document.getElementById('product_name_q').value;
  const qtt = document.getElementById('buy_qtt').value;
  const price = document.getElementById('prod_info_price').innerHTML;
  const prc_val = price.substring(price.indexOf(':')+2);
  const avail = document.getElementById('prod_info_qtt').innerHTML;
  const avl_val = avail.substring(avail.indexOf(':')+2);
  collection.findOne({_id:currentUser}).then(r=>{
      const balance = r.wallet;
      const transaction = +qtt * +prc_val;
      if (transaction > balance)
        alert('Not Enough Money');
      else if (+avl_val <= 0)
        alert('Out of Stock');
      else {
        console.log('enough money');
        updateWalletHelper(-transaction);
        updateWalletHelperWithName(uname, +transaction);
        const rate = prompt('Rate you purchase: (1-5)');
        prom = Promise.all([
        decreaseQuantity(uname, pname, qtt),
        updateRatingOfUser(uname, rate)]);
        updateOrderHistory(pname, qtt, rate);
        prom.then(()=>{alert('Purchase Successful!')});
      }
  }).then(()=>{sleep(500).then(()=>{getProduct()})})
  .catch(e=>{console.error(e)});
}
