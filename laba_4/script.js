import {findBase, toPowAndModulo} from './functionality';

const MODULO = 4231


function main() {
  
  const BASE = findBase(MODULO)

  const Alice = {
    secretData: 100,
    get publicKey() {
      return toPowAndModulo(BASE, this.secretData, MODULO)
    },
    getSecretKey() {
      return toPowAndModulo(this.bobsPublicKey, this.secretData, MODULO)
    }
  }
  const Bob = {
    secretData: 505,
    get publicKey() {
      return toPowAndModulo(BASE, this.secretData, MODULO)
    },
    getSecretKey() {
      return toPowAndModulo(this.alicesPublicKey, this.secretData, MODULO)
    }
  }

  Bob.alicesPublicKey = Alice.publicKey
  Alice.bobsPublicKey = Bob.publicKey

  console.log('Bob got: ',Bob.getSecretKey())
  console.log('Alice got: ',Alice.getSecretKey())
}

main()


